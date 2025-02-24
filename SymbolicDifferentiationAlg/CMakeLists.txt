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