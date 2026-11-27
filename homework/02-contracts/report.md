# Отчет

## Исходный код
[main.cpp](src/main.cpp)

## Отчет о работе

### Этап 1 Выделение контрактов

Объявил новые перечисления:

```cxx
enum class CommandError {None, AlreadyRunning, TemperatureOutsideStartRange, UnknownCommand};
enum class ExitCode {Ok, InputError, InvalidTemperature};
```

В CommandError добаивл UnknownCommand для удобства.

Написал функции isValidTemperature, validateCommand, executeCommand

```cxx
bool isValidTemperature(Temperature temperature)
{
    return temperature >= settings::minTemperature
        && temperature <= settings::maxTemperature;
}

CommandError validateCommand(Command command, Status status, Temperature temperature)
{
    switch (command)
    {
    case Command::Start:
        if (status != Status::Stopped) {
            return CommandError::AlreadyRunning;
        }
        if (temperature < settings::minStartTemperature || temperature > settings::maxStartTemperature) {
            return CommandError::TemperatureOutsideStartRange;
        }
        return CommandError::None;
    case Command::ShowStatus:
    case Command::Stop:
    case Command::Exit:
        return CommandError::None;
    }
    /* хоть по контракту и должна приниматься извесная команда, 
       код не будет компилироваться без этого return, поэтому я добавил CommandError::UnknownCommand */
    return CommandError::UnknownCommand;
}

Status executeCommand(Command command, Status status)
{
    switch (command)
    {
    case Command::Start:
        return Status::Running;
    case Command::ShowStatus:
        return status;
    case Command::Stop:
    case Command::Exit:
        return Status::Stopped;
    }

    /// TODO: обработка низвестной команды
    return Status::Stopped;
}
```

### Этап 2 Разделение вывода и управления

Написал функции выводв printCommandError, printCommandResult

```cxx
void printCommandError(CommandError error)
{
    switch (error)
    {
    case CommandError::AlreadyRunning:
        std::cout << "Start denied\n";
        return;
    case CommandError::TemperatureOutsideStartRange:
        std::cout << "Start denied\n";
        return;
    case CommandError::UnknownCommand:
        std::cout << "Unknown command\n";
        return;
    default:
        std::cout << "Unknown error\n";
    }
}

void printCommandResult(Command command, Status status)
{
    switch (command)
    {
    case Command::ShowStatus:
        std::cout << "Status\n";
        break;
    case Command::Start:
        std::cout << "Started\n";
        break;
    case Command::Stop:
        std::cout << "Stopped\n";
        break;
    case Command::Exit:
        break;
    }
    printStatus(status);
}

```

Функция runSession

```cxx
ExitCode runSession(Temperature temperature)
{
    Status status{Status::Stopped};
    CommandCount completed{};

    if (!isValidTemperature(temperature)) {
        std::cout << "Invalid temperature\n";
        return ExitCode::InvalidTemperature;
    }
    while (completed < settings::commandLimit)
    {
        int code{};
        std::cout << "Command 0/1/2/3: ";
        if (!(std::cin >> code)) {
            std::cout << "Input error\n";
            return ExitCode::InputError;
        }
        if (!isKnownCommand(code)) {
            printCommandError(CommandError::UnknownCommand);
            continue;
        }
        Command command{static_cast<Command>(code)};
        if (command == Command::Exit)
            break;
        CommandError error = validateCommand(command, status, temperature);
        if (error != CommandError::None) {
            printCommandError(error);
            continue;
        }
        status = executeCommand(command, status);
        printCommandResult(command, status);
        ++completed;
    }
    std::cout << "Completed: " << completed << "\n";
    telemetry::printValue(completed);
    return ExitCode::Ok;
}

```

### Этап 3 Проверки

#### Проверки отдельных функций

Я не стал делать отдельную сборку, просто объявил функцию tests() 

```cxx
void tests()
{
    assert(validateCommand(Command::Start, Status::Stopped, 0) == CommandError::None);
    assert(validateCommand(Command::Start, Status::Stopped, 40) == CommandError::None);
    assert(validateCommand(Command::Start, Status::Stopped, 41) == CommandError::TemperatureOutsideStartRange);
    assert(validateCommand(Command::Start, Status::Stopped, -1) == CommandError::TemperatureOutsideStartRange);
    assert(validateCommand(Command::Start, Status::Running, 20) == CommandError::AlreadyRunning);
    assert(validateCommand(Command::ShowStatus, Status::Running, 80) == CommandError::None);
    assert(executeCommand(Command::Start, Status::Stopped) == Status::Running);
    assert(executeCommand(Command::Stop, Status::Running) == Status::Stopped);
    assert(executeCommand(Command::ShowStatus, Status::Running) == Status::Running);
    assert(isValidTemperature(-50) == true);
    assert(isValidTemperature(100) == true);
    assert(isValidTemperature(-51) == false);
    assert(isValidTemperature(101) == false);
}
```

### Полная проверка

заменил строчку запуска программы на "-------"

```
Temperature: 20
Command 0/1/2/3: 0
Completed: 0
Count: 0
---------------------
Temperature: 20
Command 0/1/2/3: 2
Started
Running: true
Command 0/1/2/3: 2
Start denied
Command 0/1/2/3: 1
Status
Running: true
Command 0/1/2/3: 3
Stopped
Running: false
Command 0/1/2/3: 0
Completed: 3
Count: 3
---------------------
Temperature: 20
Command 0/1/2/3: 9
Unknown command
Command 0/1/2/3: -1
Unknown command
Command 0/1/2/3: 1
Status
Running: false
Command 0/1/2/3: 0
Completed: 1
Count: 1
---------------------
Temperature: 40
Command 0/1/2/3: 2
Started
Running: true
Command 0/1/2/3: 0
Completed: 1
Count: 1
---------------------
Temperature: 41
Command 0/1/2/3: 2
Start denied
Command 0/1/2/3: 0
Completed: 0
Count: 0
---------------------
Temperature: 0
Command 0/1/2/3: 2
Started
Running: true
Command 0/1/2/3: 0
Completed: 1
Count: 1
---------------------
Temperature: -1
Command 0/1/2/3: 2
Start denied
Command 0/1/2/3: 0
Completed: 0
Count: 0
---------------------
Temperature: -50
Command 0/1/2/3: 1
Status
Running: false
Command 0/1/2/3: 0
Completed: 1
Count: 1
---------------------
Temperature: -51
Invalid temperature
---------------------
Temperature: 20
Command 0/1/2/3: 1
Status
Running: false
Command 0/1/2/3: 1
Status
Running: false
Command 0/1/2/3: 1
Status
Running: false
Command 0/1/2/3: 1
Status
Running: false
Command 0/1/2/3: 1
Status
Running: false
Command 0/1/2/3: 1
Status
Running: false
Command 0/1/2/3: 1
Status
Running: false
Command 0/1/2/3: 1
Status
Running: false
Command 0/1/2/3: 1
Status
Running: false
Command 0/1/2/3: 1
Status
Running: false
Completed: 10
Count: 10
---------------------
Temperature: abc
Input error
```
