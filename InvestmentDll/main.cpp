// The functions contained in this file are pretty dummy
// and are included only as a placeholder. Nevertheless,
// they *will* get included in the shared library if you
// don't remove them :)
//
// Obviously, you 'll have to write yourself the super-duper
// functions to include in the resulting library...
// Also, it's not necessary to write every function in this file.
// Feel free to add more files in this project. They will be
// included in the resulting library.

#include <iostream>
#include <memory>
#include "Investment.h"

//#define DLL_EXPORT __declspec(dllexport)

void InvestmentDeleter( Investment *pInv )
{
    std::cout << "My investment deleter()" << std::endl;
    if( pInv != NULL ) {
        delete pInv;
        pInv = NULL;
    }
}

// DLL_EXPORT
extern "C"
{
    // A function adding two integers and returning the result
    int SampleAddInt(int i1, int i2)
    {
        return i1 + i2;
    }

    // A function doing nothing ;)
    void SampleFunction1()
    {
        // insert code here
    }

    std::shared_ptr< Investment > CreateInvestment()
    {
        std::cout << "API CreateInvestment" << std::endl;
        return std::shared_ptr< Investment >( new Investment( 20 ), InvestmentDeleter );
    }

    // A function doing nothing ;)
    int SampleFunction4()
    {
        // insert code here
        std::cout << "API SampleFunction4" << std::endl;
        return 10;
    }
}
