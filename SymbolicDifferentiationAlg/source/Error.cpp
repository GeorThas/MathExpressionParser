#include "Error.h"

Error::Error(std::string message, Type errorType) : type{ errorType }
{
    switch (errorType)
    {
    case Syntax:
        msg = "Syntax Error: " + message;
        break;
    case Math:
        msg = "Math Error: " + message;
        break;
    }
}