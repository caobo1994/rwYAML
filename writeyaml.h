#ifndef WRITEYAML_RWYAML_H
#define WRITEYAML_RWYAML_H

#include "common.h"
#include "basic_functions.h"


//Declarations
template <class T>
YAML::Node writeYAML(const T& content);

template <class T>
YAML::Node writeYAMLSimple(const T& content);

template <class T, template <class> class LIST>
YAML::Node writeYAMLList(const LIST<T>& content);

template <class T, class It>
YAML::Node writeYAMLList(It begin, It end);

template <class K, class V, template<class> class MAP>
YAML::Node writeYAMLMap(const MAP<T>& content);

template <class T, class It>
YAML::Node writeYAMLMap(It begin, It end);

//Definitions
template <class T>
YAML::Node writeYAMLSimple(const T& content)
{
  return YAML::Node(std::to_string(content));
}

template <class T, template <class> class LIST>
YAML::Node writeYAMLList(const LIST<T>& content)
{
  return writeYAMLList(content.begin(), content.end());
}

template <class It>
YAML::Node writeYAMLList(It begin, It end)
{
  YAML::Node node;
  size_t count = 0;
  for (auto x = begin; x != end; ++x)
  {
    node[count] = writeYAML(*It);
    ++count;
  }
  return node;
}

template <class K, class V, template<class> class MAP>
YAML::Node writeYAMLMap(const MAP<T>& content)
{
  return writeYAMLMap(content.begin(), content.end());
}

template <class It>
YAML::Node writeYAMLMap(It begin, It end)
{
  YAML::Node node;
  for (auto x = begin; x != end; ++x)
  {
    node[std::to_string(x->first)] = writeYAML(x->second);
  }
  return node;
}


#endif
