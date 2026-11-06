#include <iostream>
#include <string>
#include <windows.h>

using std::string;
using std::cin, std::cout;

string name_event;
const int ticket_price = 200;
int ticket_cnt = 3;
const int order_fee = 25;
int issued_tickets = 0;
bool issue_ack = false;


int main()
{
    // переключаем раскладку вывода на UTF8, 
    // потому что исходный текст у меня в UTF8 и в нем есть русские буквы.
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    cout << "Введите имя покупателя и событие>";
    std::getline(cin, name_event);

    int order_total = ticket_price * ticket_cnt + order_fee;

    std::print(cout, 
        "\nIT MEETUP TICKET\n"
        "Покупатель и событие: {}\n"
        "Цена билета {}\n"
        "Количество билетов {}\n"
        "Сбор {}\n"
        "Итого {}\n"
        "Выдано до {}\n"
        "Статус выдачи до {}\n",
        name_event, ticket_price, ticket_cnt, order_fee, order_total,
        issued_tickets, issue_ack
    );

    int issued_tickets_copy = issued_tickets;
    issued_tickets = ticket_cnt;
    issue_ack = true;

    std::print(cout, 
        "Выдано после {}\n"
        "Статус выдачи после {}\n"
        "Сохранненное значение выдано {}\n",
        issued_tickets, issue_ack, issued_tickets_copy);

    return 0;
}
