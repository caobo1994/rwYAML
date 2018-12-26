/*
Copyright information needed.
Best decided by author of the whole library.
*/

/*
Passed with standard c++14, c++17 and compiler gcc-7.3.0
*/

#include "readyaml.hpp"
std::logic_error append_logic_error(
  const std::logic_error& old_exception,
  const std::string& new_content)
  throw()
{
  std::string content = std::string(old_exception.what()) + new_content;
  return std::logic_error(content.c_str());
}

/*
Realize simple types for readYAMLObj
Currently, the types we realized are listed as follows.
bool, all the integer types(different size, signed or unsigned),
all the real-number types, char, std::string
*/
#define SIMPLEREAD(T)                                        \
  template <>                                                \
  size_t readYAMLObj<T>(const YAML::Node& source, T& dest) { \
    return readYAMLObjScalar(source, dest);                  \
  }                                                          \
  template size_t readYAMLObj<T>(const YAML::Node& source, T& dest);

SIMPLEREAD(bool)

SIMPLEREAD(int8_t)
SIMPLEREAD(int16_t)
SIMPLEREAD(int32_t)
SIMPLEREAD(int64_t)

SIMPLEREAD(uint8_t)
SIMPLEREAD(uint16_t)
SIMPLEREAD(uint32_t)
SIMPLEREAD(uint64_t)

SIMPLEREAD(float)
SIMPLEREAD(double)
SIMPLEREAD(long double)

SIMPLEREAD(char)
SIMPLEREAD(std::string)

#undef SIMPLEREAD
