
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
        std::cout << "Compare ( -1 > 1U ): "
            << std::boolalpha << ( -1 > 1U ) << std::endl;
        std::cout << "Safe Compare ( -1 > 1U ): "
            << std::boolalpha << safe_compare::is_greater( -1, 1U ) << std::endl;
        std::cout << "Compare ( -1 < 1U ): "
            << std::boolalpha << ( -1 < 1U ) << std::endl;
        std::cout << "Safe Compare ( -1 < 1U ): "
            << std::boolalpha << safe_compare::is_less( -1, 1U ) << std::endl;
        std::cout << "Compare ( -1 >= 1U ): "
            << std::boolalpha << ( -1 >= 1U ) << std::endl;
        std::cout << "Safe Compare ( -1 >= 1U ): "
            << std::boolalpha << safe_compare::is_greater_equal( -1, 1U ) << std::endl;
        std::cout << "Compare ( -1 <= 1U ): "
            << std::boolalpha << ( -1 <= 1U ) << std::endl;
        std::cout << "Safe Compare ( -1 <= 1U ): "
            << std::boolalpha << safe_compare::is_less_equal( -1, 1U ) << std::endl;
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
