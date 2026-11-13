#include <iostream>
#include <string>
#include <windows.h>
#include "cin_tee.hpp"


int main()
{
    // переключаем раскладку вывода на UTF8, 
    // потому что исходный текст у меня в UTF8 и в нем есть русские буквы.
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int count; ///< количество показаний

    std::cout << "Count: ";
    std::cin >> count;
    if (std::cin.fail()) {
        std::cout << "Input error\n";
        return 1;
    }
    if (count < 0 || count > 10) {
        std::cout << "Invalid count\n";
        return 1;
    }
    
    unsigned valid = 0; ///< счётчик принятых показаний
    unsigned invalid = 0; ///< счётчик отклоненных показаний
    unsigned working = 0; ///< счётчик рабочих показаний
    int sum = 0; ///< сумма принятых температур показаний

    for(int i = 0; i < count; ++i) {
        int temp; ///< показания датчика
        std::cout << "Value: ";
        std::cin >> temp;
        if (std::cin.fail()) {
            std::cout << "\nInput error\n";
            return 1;
        }
        if (temp < -50 || temp > 100) {
            ++invalid;
            std::cout << "Rejected\n";
            continue;
        }
        sum += temp;
        ++valid;
        if (temp >= 0 && temp <= 40) {
            ++working;
        }
        std::cout << "Accepted\n";
    }
    std::print(std::cout,
        "Valid: {}\n"
        "Invalid: {}\n"
        "Working: {}\n",
        valid, invalid, working
    );
    if (valid) {
        std::print(std::cout,
            "Average: {}\n",
            static_cast<double>(sum) / valid);
    }
    return 0;
}
