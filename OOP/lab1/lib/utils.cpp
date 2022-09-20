#include <iostream>
#include "utils.h"

int read_num() {
    int num;
    while(!(std::cin >> num)){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Введите корректное целое число:" << std::endl;
    }
    return num;
}

int reverse(int num) {
    bool is_negative = false;
    if (num < 0) {
        num = - num;
        is_negative = true;
    }

    int result = 0;
    while(num) {
        result *= 10;
        result += num % 10;
        num /= 10;
    }
    return is_negative ? -result : result;
}