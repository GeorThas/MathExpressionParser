cmake_minimum_required(VERSION 3.10)  # Укажите минимальную версию CMake
project(MathParseLib)                     # Укажите имя вашего проекта


set(CMAKE_CXX_STANDARD 20)  # Укажите стандарт C++ (например, 11, 14, 17, 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Обязательный стандарт

set( SOURCE_LIB 
    source/Error.cpp 
    source/ExpressionTree.cpp 
    source/Node.cpp 
    source/ShuntingYardAlg.cpp 
    source/Token.cpp 
    source/Tokenizator.cpp
    #source/main.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers)

# Включение экспорта всех символов для создания динамической библиотеки
set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

# Создание динамической библиотеки
add_library( MathParseLib SHARED ${SOURCE_LIB})

target_compile_definitions(MathParseLib 
    PRIVATE 
        DIFFLIB_EXPORT
)