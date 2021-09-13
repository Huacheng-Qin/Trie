#ifndef ILLEGAL_EXCEPTION_HPP
#define ILLEGAL_EXCEPTION_HPP
#include <iostream>

class illegal_exception {
    public:
    illegal_exception() = delete;
    illegal_exception(std::string what_arg);
    ~illegal_exception() = default;
    const std::string& what() const;

    private:
    const std::string m_what;
};

#include "illegal_exception_impl.hpp"
#endif
