#include <iostream>
#include <cassert>


using Temperature = int;
using CommandCount = int;

enum class Command : int
{
    Exit = 0,
    ShowStatus = 1,
    Start = 2,
    Stop = 3
};

enum class Status { Stopped, Running };

enum class CommandError {None, AlreadyRunning, TemperatureOutsideStartRange, UnknownCommand};

enum class ExitCode {Ok, InputError, InvalidTemperature};

namespace settings
{
    constexpr Temperature minTemperature{-50};
    constexpr Temperature maxTemperature{100};
    constexpr Temperature minStartTemperature{0};
    constexpr Temperature maxStartTemperature{40};
    constexpr CommandCount commandLimit{10};
}

bool isValidTemperature(Temperature temperature)
{
    return temperature >= settings::minTemperature
        && temperature <= settings::maxTemperature;
}

bool canStart(Status status, Temperature temperature,
              Temperature maxTemp = settings::maxStartTemperature)
{
    return status == Status::Stopped
        && temperature >= settings::minStartTemperature
        && temperature <= maxTemp;
}

bool isKnownCommand(int code)
{
    return code == static_cast<int>(Command::Exit)
        || code == static_cast<int>(Command::ShowStatus)
        || code == static_cast<int>(Command::Start)
        || code == static_cast<int>(Command::Stop);
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

namespace telemetry
{
    void printValue(int value)
    {
        std::cout << "Count: " << value << "\n";
    }

    void printValue(double value)
    {
        std::cout << "Reading: " << value << "\n";
    }

    void printSummary(int commandCount, double reading)
    {
        printValue(commandCount);
        printValue(reading);
    }
}

void printStatus(Status status)
{
    std::cout << "Running: "
              << (status == Status::Running) << "\n";
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

int main()
{
    std::cout << std::boolalpha;

    tests();

    Temperature temperature{};
    std::cout << "Temperature: ";
    if (!(std::cin >> temperature)) {
        std::cout << "Input error\n";
        return 1;
    }
    return static_cast<int>(runSession(temperature));
}
