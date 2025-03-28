cmake_minimum_required(VERSION 3.10)  # Укажите минимальную версию CMake
project(SymDiffLib)                     # Укажите имя вашего проекта


set(CMAKE_CXX_STANDARD 20)  # Укажите стандарт C++ (например, 11, 14, 17, 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Обязательный стандарт

set( SOURCE_LIB 
    source/diff.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers)

link_directories(${PROJECT_SOURCE_DIR}/lib)

# Включение экспорта всех символов для создания динамической библиотеки
set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

# Создание динамической библиотеки
add_library( SymDiffLib SHARED ${SOURCE_LIB})

target_link_libraries(SymDiffLib PRIVATE MathParseLib)