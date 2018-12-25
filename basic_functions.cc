#include "basic_functions.h"

std::logic_error append_logic_error(
  const std::logic_error& old_exception,
  const std::string& new_content)
  throw()
{
  std::string content = std::string(old_exception.what()) + new_content;
  return std::logic_error(content.c_str());
}
