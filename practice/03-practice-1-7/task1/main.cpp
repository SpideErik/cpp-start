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

    std::string name;
    std::cout << "Name: ";
    std::getline(std::cin, name);

    int tickets_cnt = 0;             ///< количество билетов
    double ticket_price = 0.0;       ///< Цена одного билета
    bool is_discount = 0;            ///< Признак скидки
    const int discount_percent = 10; ///< скидка в %

    std::cout << "Tickets price discount (0/1): ";
    std::cin >> tickets_cnt >> ticket_price >> is_discount;
    if (std::cin.fail()) {
        std::cout << "\nInput error\n";
        return 1;
    }
    if (tickets_cnt < 1 || tickets_cnt > 10  ||
        ticket_price <= 0 || ticket_price > 5000) {
            std::cout << "Invalid data\n";
            return 1;
    }

    double base = ticket_price * tickets_cnt; ///< цена без скидки
    double discount = (base * discount_percent / 100) * is_discount; ///< скидка
    double total = base - discount;

    std::print(std::cout,
        "Customer: {}\n"
        "Tickets: {}\n"
        "Base: {}\n"
        "Discount applied: {}\n"
        "Discount: {}\n"
        "Total: {}\n",
        name, tickets_cnt, base, is_discount, discount, total
    );
    return 0;
}
