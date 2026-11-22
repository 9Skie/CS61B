#include "Arithmetic.hpp"
#include <iostream>
int main() {
    int num1, num2;
    std::cout << "Give me a number! (no decimals, please)\n";
    if (!(std::cin >> num1))
        return 1;
    std::cout << "Give me another number! (still no decimals)\n";
    if (!(std::cin >> num2))
        return 1;
    std::cout << "The product of " << num1 << " and " << num2
              << " is: " << Arithmetic::product(num1, num2) << '\n';
    std::cout << "The sum of " << num1 << " and " << num2 << " is: " << Arithmetic::sum(num1, num2)
              << '\n';
}
