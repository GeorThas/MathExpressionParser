#pragma once
#include <string>

class Error
{
public:

    enum Type
    {
        Syntax,
        Math
    } type;

    Error(std::string message, Type errorType);

    std::string what()
    {
        return msg;
    }

private:
    std::string msg;
};