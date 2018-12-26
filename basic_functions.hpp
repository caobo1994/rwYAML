#ifndef BASIC_FUNCTIONS_RWYAML_HPP
#define BASIC_FUNCTIONS_RWYAML_HPP

#include "common.hpp"

/*
Appends new error information to the error information
 of an old std::append_logic_error
object to produce and return a new std::logic_error object.
*/
std::logic_error append_logic_error(
    const std::logic_error& old_exception,
    const std::string& new_content) throw();


#endif
