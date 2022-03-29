#include <iostream>
#include <windows.h>
#include <memory>
#include "Investment.h"
//#include <Boost>

HINSTANCE g_hDll = NULL; // instance handle for dll import
typedef std::shared_ptr<Investment>(*lpCreateInvestment)(void); // dll function pointer declaration

void WrongDeleter( Investment *pInv )
{
    std::cout << "Wrong deleter" << std::endl;
    if( pInv != NULL ) {
        delete pInv;
        pInv = NULL;
    }
}

void Example( void )
{
    // get function pointer
    lpCreateInvestment pCreateInvFunc = (lpCreateInvestment)GetProcAddress( g_hDll, "CreateInvestment" );

//    std::shared_ptr< Investment > SharedPtr( pCreateInvFunc().get(), WrongDeleter ); // <--------Try uncomment this
    std::shared_ptr< Investment > SharedPtr = pCreateInvFunc();

    std::cout << "Investment days held = " << SharedPtr->GetDaysHeld() << std::endl;

    std::cout << "Before leaving example" << std::endl;
}

int main()
{
    std::cout << "Hello InvestmentDll user!" << std::endl;

    g_hDll = LoadLibrary("libInvestmentDll.dll");

    Example();

    FreeLibrary( g_hDll );

    system("pause");
    return 0;
}
