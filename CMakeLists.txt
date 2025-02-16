cmake_minimum_required(VERSION 3.10)  # Укажите минимальную версию CMake
project(MyProject)                     # Укажите имя вашего проекта

set(CMAKE_CXX_STANDARD 20)  # Укажите стандарт C++ (например, 11, 14, 17, 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Обязательный стандарт

# Добавьте поддиректории

add_subdirectory(SymbolicDifferentiationAlg)                  # Поддиректория с библиотеками
add_subdirectory(Client)                 # Поддиректория с исходным кодом
#target_link_libraries(math_parese PRIVATE shared_lib )