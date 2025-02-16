# Проверка версии CMake
cmake_minimum_required( VERSION 3.4.0 )

# Название проекта и проверка доступности компиляторя с++
project( shared_lib CXX )			

set(CMAKE_CXX_STANDARD 20)  # Укажите стандарт C++ (например, 11, 14, 17, 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Обязательный стандарт

# Установка переменной со списком исходников
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
add_library( shared_lib SHARED ${SOURCE_LIB})

#add_executable( math_parese ${SOURCE_LIB} source/main.cpp)