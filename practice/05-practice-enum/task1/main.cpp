#include <iostream>
#include <windows.h>


using std::cout, std::print, std::cin;

enum class Operator : char  {
    Add = '+',
    Sub = '-',
    Mul = '*',
    Div = '/'
};

double add(double a, double b)
{
    return a + b;
}

double mul(double a, double b)
{
    return a * b;
}

double sub(double a, double b)
{
    return a - b;
}

double div(double a, double b)
{
    if (b == 0)
        return std::nan("");
    return a / b;
}


int main()
{
    // переключаем раскладку вывода на UTF8, 
    // потому что исходный текст у меня в UTF8 и в нем есть русские буквы.
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    double n1, n2;
    char op_input;

    cout << "Введите число операция число через пробел\nнапример 1 + 3: ";

    cin >> n1 >> op_input >> n2;

    Operator op = static_cast<Operator>(op_input);

    double res;

    switch(op) {
        case Operator::Add:
            res = add(n1, n2);
            break;
        case Operator::Sub:
            res = sub(n1, n2);
            break;
        case Operator::Mul:
            res = mul(n1, n2);
            break;
        case Operator::Div:
            res = div(n1, n2);
            break;
        default:
            cout << "неизвестная операция\n";
    }

    cout << n1 << op_input << n2 << "=" << res << "\n";


}
