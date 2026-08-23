#include <iostream>

void printPrimeFactors(int n) {
    // 1. Handle all the factors of 2
    while (n % 2 == 0) {
        std::cout << 2 << " ";
        n = n / 2;
    }

    // 2. n must be odd at this point, so we can skip even numbers
    // We only need to check up to the square root of n
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            std::cout << i << " ";
            n = n / i;
        }
    }

    // 3. If n is still greater than 2, then n itself is prime
    if (n > 2) {
        std::cout << n << " ";
    }
}

int main() {
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;

    std::cout << "Prime factors: ";
    printPrimeFactors(number);
    std::cout << std::endl;

    return 0;
}
