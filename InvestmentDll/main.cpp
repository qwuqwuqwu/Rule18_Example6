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
#include <tr1/memory>
#include <tr1/shared_ptr.h>
//#include <memory>
#include "Investment.h"

//#define DLL_EXPORT __declspec(dllexport)

void Deleter( Investment *pInv )
{
    std::cout << "Deleter()" << std::endl;
    if( pInv != NULL ) {
        delete pInv;
        pInv = NULL;
    }
    else {
        std::cout << "null pointer" << std::endl;
    }
}

void DeleterII( Investment *pInv )
{
    std::cout << "DeleterII()" << std::endl;
    if( pInv != NULL ) {
        delete pInv;
        pInv = NULL;
    }
    else {
        std::cout << "null pointer" << std::endl;
    }
}

// DLL_EXPORT
extern "C"
{
    int SampleFunction()
    {
        // insert code here
        std::cout << "API SampleFunction" << std::endl;
        return 10;
    }

    std::tr1::shared_ptr< Investment > CreateInvestment( const int& nDaysHeld, bool *pbCreateSuccess )
    {
        std::cout << "API CreateInvestment()==================== Start" << std::endl;
        //std::tr1::shared_ptr< Investment >retVal( static_cast< Investment* >( 0 ), Deleter );
        std::tr1::shared_ptr< Investment >retVal( static_cast< Investment* >( 0 ), Deleter );

        if( nDaysHeld == 2 ) {
            retVal = std::tr1::shared_ptr< Investment >( new Investment( nDaysHeld ), DeleterII );
            *pbCreateSuccess = true;
        }
        else if( nDaysHeld == 0 ) {
            // do nothing
            *pbCreateSuccess = false;
        }
        else {
            retVal = std::tr1::shared_ptr< Investment >( new Investment( nDaysHeld ), Deleter );
            *pbCreateSuccess = true;
        }

        std::cout << "API CreateInvestment()==================== End" << std::endl;
        return retVal;

//        std::cout << "API CreateInvestment" << std::endl;
//        return std::tr1::shared_ptr< Investment >( new Investment( nDaysHeld ), InvestmentDeleter );
    }
}
