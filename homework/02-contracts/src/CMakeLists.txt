cmake_minimum_required(VERSION 3.15)

project(Practice LANGUAGES CXX)

# Явно задаем стандарт C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Если компилятор MSVC (Visual Studio / Build Tools), 
# включаем поддержку UTF-8 в консоли, чтобы не плыли русские буквы
if(MSVC)
    add_compile_options(/utf-8 /W4)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Аналогичный уровень предупреждений для GCC (и Clang)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Главный исполняемый файл
add_executable(app main.cpp)
