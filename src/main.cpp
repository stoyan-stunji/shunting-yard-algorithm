#include "Implementation.h"

int main() 
{
    try
    {
        const std::string test_1 = "3+4*2/(1-5)^2^3"; // 3
        const std::string test_2 = "(-3)*(-2^3)"; // 18
        const std::string test_3 = "(3) + (4)"; // 7
        const std::string test_4 = "(2*3+3*4)"; // 24
        const std::string test_5 = "2 + 3 * 4"; // 14
        std::cout << evaluate(test_3);
    }
    catch(const char* e)
    {
        std::cout << e << '\n';
    }
    
}