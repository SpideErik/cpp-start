#include <iostream>
#include <string>
#include <windows.h>

using std::string;
using std::cin, std::cout;

string full_name;
string group;
int age = 17;
double experience = 2.5;
bool project_ready = true;
const int complete_pair = 2;
int complete_tasks = 0;



int main()
{
    // переключаем раскладку вывода на UTF8, 
    // потому что исходный текст у меня в UTF8 и в нем есть русские буквы.
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    cout << "Введите имя и фамилию>";
    std::getline(cin, full_name);

    cout << "Введите группу>";
    std::getline(cin, group);

    int complete_tasks_copy = complete_tasks;

    std::print(cout, 
        "\nSTUDENT PROFILE\n"
        "ФИО {}\n"
        "ГРУППА {}\n"
        "Course: C++\n"
        "Возраст {}\n"
        "Опыт обучения в годах {}\n"
        "Готовность к проекту {}\n"
        "Количество пройденных пар {}\n"
        "Счётчик выполненных заданий до {}\n",
        full_name, group, age, experience, project_ready, complete_pair, complete_tasks
    );

    complete_tasks += 5;
    
    std::print(cout, 
        "Счётчик выполненных заданий после {}\n"
        "Счётчик выполненных заданий сохраненный {}\n",
        complete_tasks,
        complete_tasks_copy
    );

    return 0;
}
