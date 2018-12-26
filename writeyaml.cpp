#include "writeyaml.hpp"

#define SIMPLEWRITE(T) \
template <class T> \
YAML::Node writeYAML(const T& content) \
{ \
  return writeYAMLSimple(content); \
} \
template
YAML::Node writeYAML<T>(const T& content);

SIMPLEWRITE(bool)

SIMPLEWRITE(int8_t)
SIMPLEWRITE(int16_t)
SIMPLEWRITE(int32_t)
SIMPLEWRITE(int64_t)

SIMPLEWRITE(uint8_t)
SIMPLEWRITE(uint16_t)
SIMPLEWRITE(uint32_t)
SIMPLEWRITE(uint64_t)

SIMPLEWRITE(float)
SIMPLEWRITE(double)
SIMPLEWRITE(long double)

SIMPLEWRITE(char)
SIMPLEWRITE(std::string)

#undef SIMPLEWRITE

using namespace std;
