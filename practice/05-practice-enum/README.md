# Практика по enum

Калькулятор при помощи enum

Перечисления через enum class (современный стандарт), например:

```cxx
enum class Operator : char  {
    Add = '+',
    Sub = '-',
    Mul = '*',
    Div = '/'
};
```

доступ похож на namespace, например:

```cxx
Operator::Add
```

значения в enum преобразовывают через static_cast, например:

```cxx
Operator op = static_cast<Operator>(op_input);
```

исзодный код:

[calculator](task1/main.cpp)
