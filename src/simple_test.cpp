
// --- App Includes --- //
#include "safe_compare.h"

// --- Standard Includes --- //
#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////
int main(
    int argc,
    char** argv)
{
    try
    {
        safe_compare::greater< int, unsigned int > safe_greater;
        std::cout << safe_greater( -1, 1 ) << std::endl;
        std::cout << safe_greater( 1, 1 ) << std::endl;
        std::cout << safe_greater( 2, 1 ) << std::endl;
    }
    catch( std::exception const& e )
    {
        std::cerr << "*** std::exception caught: "
            << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////
