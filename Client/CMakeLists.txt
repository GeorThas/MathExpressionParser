# Установка переменной со списком исходников
set( SOURCE_LIB 
    source/main.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers)

add_executable( math_parese ${SOURCE_LIB} source/main.cpp)

target_link_libraries(math_parese PRIVATE MathParseLib)