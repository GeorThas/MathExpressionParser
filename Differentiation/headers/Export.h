#pragma once

#ifdef _WIN32
    #ifdef DIFFLIB_EXPORT
        #define DIFFLIB_API __declspec(dllexport)
    #else
        #define DIFFLIB_API __declspec(dllimport)
    #endif
#else
    #define DIFFLIB_API
#endif