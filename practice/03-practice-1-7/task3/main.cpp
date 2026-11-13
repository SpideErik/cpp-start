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

    int budget; ///< бюджет

    std::cout << "Budget: ";
    std::cin >> budget;
    if (std::cin.fail()) {
        std::cout << "\nInput error\n";
        return 1;
    }
    if (budget < 0 || budget > 100000) {
        std::cout << "Invalid budget\n";
        return 1;
    }

    const unsigned max_price_cnt = 10; ///< максимальное кол-во цен
    int remaining = budget; ///< осталось денег
    int spent = 0; ///< потрачено денег
    int items = 0; ///< кол-во успешных покупок

    for(unsigned i=0; i < max_price_cnt; ++i) {
        int price;
        std::cout << "Price (0 stop): ";
        std::cin >> price;
        if (std::cin.fail()) {
            std::cout << "\nInput error\n";
            return 1;
        }
        if (price == 0)
            break;
        if (price < 0 || price > 100000) {
            std::cout << "Invalid price\n";
            continue;
        }
        if (price > remaining) {
            std::cout << "Not enough money\n";
            continue;
        }
        remaining -= price;
        spent += price;
        ++items;
        std::cout << "Added\n";
    }
    std::print(std::cout,
        "Items: {}\n"
        "Spent: {}\n"
        "Remaining: {}\n",
        items, spent, remaining);

    return 0;
}
