#include <iostream>
#include <string>
#include <windows.h>

using std::string;
using std::cin, std::cout;

string name_dish;
const double portion_price = 145.5;
int portion_cnt = 3;
const double order_fee = 20.0;
bool payment_state = false;


int main()
{
    // переключаем раскладку вывода на UTF8, 
    // потому что исходный текст у меня в UTF8 и в нем есть русские буквы.
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    cout << "Введите имя покупателя и блюдо>";
    std::getline(cin, name_dish);

    double order_price = portion_price * portion_cnt;
    double order_total = order_price + order_fee;

    std::print(cout, 
        "\nCAFE ORDERC\n"
        "Покупатель и блюдо: {}\n"
        "Цена порции {}\n"
        "Количество порций {}\n"
        "Стоимость без сбора {}\n"
        "Сбор {}\n"
        "Итого {}\n",
        name_dish, portion_price, portion_cnt, order_price, order_fee, order_total
    );


    return 0;
}
