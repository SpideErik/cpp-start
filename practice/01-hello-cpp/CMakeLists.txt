cmake_minimum_required(VERSION 3.15)

# Имя проекта (можно латинскими буквами)
project(HelloCpp LANGUAGES CXX)

# Явно задаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Если компилятор MSVC (Visual Studio / Build Tools), 
# включаем поддержку UTF-8 в консоли, чтобы не плыли русские буквы
if(MSVC)
    add_compile_options(/utf-8)
endif()

# Главный исполняемый файл
add_executable(app main.cpp)
