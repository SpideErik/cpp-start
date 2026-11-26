#include <iostream>
#include <windows.h>


using std::cout, std::print, std::cin;

/*
Порядок выполнения
1. Подготовьте массив. Объявите константу размера 6 и массив int. Запросите шесть
измерений в диапазоне от −50 до 50. Используйте цикл for и сохраните каждое число в
очередной ячейке. Ввод считается корректным.
2. Подготовьте накопители. Создайте переменные sum и positive со значением 0. Для
minValue и maxValue возьмите значение первого элемента уже заполненного массива.
3. Обойдите массив. В новом цикле переберите все элементы. Прибавляйте каждый к
sum. Если текущее число меньше minValue, обновляйте минимум; если больше maxValue,
обновляйте максимум. При значении строго больше нуля увеличивайте positive.
4. Рассчитайте среднее. Разделите сумму на размер массива, предварительно
преобразовав её через static_cast<double>(sum). Подключите <iomanip> и используйте
std::fixed и std::setprecision(2) для вывода среднего с двумя знаками после точки.
5. Выведите результат. Покажите сумму, минимальную и максимальную температуру,
среднее и количество положительных измерений.
*/
int main()
{
    // переключаем раскладку вывода на UTF8, 
    // потому что исходный текст у меня в UTF8 и в нем есть русские буквы.
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    constexpr int size = 6;
    int temp[size]{};

    cout << "Введите 6 измерений в диапазоне от −50 до 50 через пробел: ";
    for(unsigned i = 0; i < size; ++i) {
        cin >> temp[i];
    }

    int sum = 0;
    int positive = 0;
    int min_value, max_value;
    min_value = max_value = temp[0];

    for(unsigned i = 0; i < size; ++i) {
        sum += temp[i];
        if (temp[i] > 0) {
            ++positive;
        }
        if (temp[i] < min_value) {
            min_value = temp[i];
        }
        if (temp[i] > max_value) {
            max_value = temp[i];
        }
    }

    double average = static_cast<double>(sum) / size;

    std::print(cout,
        "Сумма: {}\n"
        "Минимум: {}\n"
        "Максимум: {}\n"
        "Среднее: {:.2}\n"
        "Положительных: {}\n",
        sum, min_value, max_value, average, positive
    );

    return 0;
}
