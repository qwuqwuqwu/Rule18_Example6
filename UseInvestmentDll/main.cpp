#include <iostream>
#include <windows.h>

#include <tr1/memory>
#include <tr1/shared_ptr.h>

#include "Investment.h"

HINSTANCE g_hDll = NULL; // instance handle for dll import
typedef std::tr1::shared_ptr<Investment>(*lpCreateInvestment)( const int&, bool* ); // dll function pointer declaration

void WrongDeleter( Investment *pInv )
{
    std::cout << "Wrong deleter" << std::endl;
    if( pInv != NULL ) {
        delete pInv;
        pInv = NULL;
    }
}

void PrintDays( std::tr1::shared_ptr< Investment > Inv )
{
    std::cout << "Days held by investment " << Inv.get() << " is " << Inv->GetDaysHeld() << std::endl;
}

void Example( const int& nDaysHeld )
{
    // print something when function start
    std::cout << std::endl;
    std::cout << "Example Start" << nDaysHeld << std::endl;

    // get function pointer
    lpCreateInvestment pCreateInvFunc = (lpCreateInvestment)GetProcAddress( g_hDll, "CreateInvestment" );

    // get investment by calling dll function
    bool bSuccess = false;
    std::tr1::shared_ptr< Investment > SharedPtr = pCreateInvFunc( nDaysHeld, &bSuccess );
    // std::tr1::shared_ptr< Investment > SharedPtr( pCreateInvFunc( nDaysHeld, &bSuccess ).get(), WrongDeleter ); // <--------Try uncomment this
    // Original deleter will be called before new WrongDeleter is assigned

    if( bSuccess ) {
        PrintDays( SharedPtr );
    }
    else {
        std::cout << "Create unsuccessfully" << std::endl;
    }

    std::cout << "Example End" << std::endl;
}

int main()
{
    std::cout << "Hello InvestmentDll user!" << std::endl;

    g_hDll = LoadLibrary("libInvestmentDll.dll");

    Example( 10 );
    Example( 2 );
    Example( 0 );

    FreeLibrary( g_hDll );

    system("pause");
    return 0;
}
