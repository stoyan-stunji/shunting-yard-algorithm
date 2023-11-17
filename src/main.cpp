#include "Implementation.h"

int main() 
{
    try
    {
        const std::string test_1 = "3+4*2/(1-5)^2^3"; // 3 - Wikipedia
        const std::string test_2 = "(-3)*(-2^3)"; // 24
        const std::string test_3 = "(3) + (4)"; // 7
        const std::string test_4 = "(2*3+3*4)"; // 18
        const std::string test_5 = "2 + 3 * 4"; // 14
        const std::string test_6 = "3 + 4"; // 7 - Wikipedia
        const std::string test_7 = "0/3"; // 7 - Wikipedia
        const std::string test_8 = "3 / 0"; // exception - Wikipedia

        std::cout << evaluate(test_1) << '\n';
        std::cout << evaluate(test_2) << '\n';
        std::cout << evaluate(test_3) << '\n';
        std::cout << evaluate(test_4) << '\n';
        std::cout << evaluate(test_5) << '\n';
        std::cout << evaluate(test_6) << '\n';
        std::cout << evaluate(test_7) << '\n';
        std::cout << evaluate(test_8) << '\n';
    }
    catch(const char* e)
    {
        std::cout << e << '\n';
    }
    
}