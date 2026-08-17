#include "statistics.h"

double mean(std::array<int, 10>& data) {
    double sum = 0.0;

    for (int index = 0; index < 10; index++) {
        sum += data[index];
    }

    return sum / 10.0;
}

double median(std::array<int, 10>& data) {
    std::array<int, 10> sorted_data = data;

    for (int pass = 0; pass < 9; pass++) {
        for (int index = 0; index < 9 - pass; index++) {
            if (sorted_data[index] > sorted_data[index + 1]) {
                int temporary = sorted_data[index];
                sorted_data[index] = sorted_data[index + 1];
                sorted_data[index + 1] = temporary;
            }
        }
    }

    return (static_cast<double>(sorted_data[4]) + sorted_data[5]) / 2.0;
}
