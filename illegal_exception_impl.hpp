#ifndef ILLEGAL_EXCEPTION_IMPL_HPP
#define ILLEGAL_EXCEPTION_IMPL_HPP
#include <iostream>
#include "illegal_exception.hpp"

illegal_exception::illegal_exception(std::string what_arg):
    m_what(std::move(what_arg)) {}

const std::string& illegal_exception::what() const {
    return m_what;
}

#endif
