#include <array>
#include <iostream>

#include "statistics.h"

int main() {
    std::array<int, 10> data = {};

    std::cout << "Enter 10 integers:\n";

    for (int index = 0; index < 10; index++) {
        if (!(std::cin >> data[index])) {
            std::cerr << "Invalid input. Please enter 10 integers.\n";
            return 1;
        }
    }

    std::cout << "Mean: " << mean(data) << '\n';
    std::cout << "Median: " << median(data) << '\n';

    return 0;
}
