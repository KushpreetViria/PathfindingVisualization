#pragma once

#include <exception>
#include <string>

class MyException : public std::exception {
public:
    MyException(const char* msg = "") : std::exception(msg) {}
};