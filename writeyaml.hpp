#ifndef WRITEYAML_RWYAML_HPP
#define WRITEYAML_RWYAML_HPP

#include "common.hpp"
#include "basic_functions.hpp"


//Declarations
template <class T>
YAML::Node writeYAML(const T& content);

template <class It>
YAML::Node writeYAML(It begin, It end);

template <class T>
YAML::Node writeYAMLSimple(const T& content);

template <class T>
YAML::Node writeYAMLPointer(T begin, T end);

#define POINTERWRITE(TP) \
template <class T> \
YAML::Node writeYAML(TP begin, TP end) \
{ \
  return writeYAMLPointer(begin, end); \
} \

POINTERWRITE(T*)
POINTERWRITE(std::weak_ptr<T>)
POINTERWRITE(std::shared_ptr<T>)

template <class T1, class T2>
YAML::Node writeYAML(const std::pair<T1, T2>& content);

template <class T, template <class> class LIST>
YAML::Node writeYAMLList(const LIST<T>& content);

template <class T, template <class> class LIST>
YAML::Node writeYAMLList(
  LIST<T>::const_iterator begin,
  LIST<T>::const_iterator end);

#define LISTWRITE(LIST) \
template <class T> \
YAML::Node writeYAML(const LIST<T>& content) \
{ \
  return writeYAMLList(content); \
} \
template <class T> \
YAML::Node writeYAML(LIST<T>::const_iterator begin, LIST<T>::const_iterator end) \
{ \
  return writeYAMLList(begin, end) \
} \

LISTWRITE(std::vector)
LISTWRITE(std::list)
LISTWRITE(std::forward_list)
LISTWRITE(std::deque)

LISTWRITE(std::set)
LISTWRITE(std::multiset)
LISTWRITE(std::unordered_set)
LISTWRITE(std::unordered_multiset)

template <class K, class V, template<class> class MAP>
YAML::Node writeYAMLMap(const MAP<K, V>& content);

template <class K, class V, template<class> class MAP>
YAML::Node writeYAMLMap(
  MAP<K, V>::const_iterator begin,
  MAP<K, V>::const_iterator end);

#define MAPWRITE(MAP) \
template <class K, class V> \
YAML::Node writeYAML(const MAP<K, V>& content) \
{ \
  return writeYAMLMap(content); \
} \
template <class K, class V>
YAML::Node writeYAML(MAP<K, V>::const_iterator begin, MAP<K, V>::const_iterator end)
{ \
  return writeYAMLMap(begin, end); \
} \

MAPWRITE(std::map)
MAPWRITE(std::multimap)
MAPWRITE(std::unordered_map)
MAPWRITE(std::unordered_multimap)

template <class T, template<class> class LIST>
YAML::Node writeYAMLOrder(
  LIST<T>::const_iterator begin,
  LIST<T>::const_iterator end,
  const auto& Op = std::less<T>());

template <class T, template<class> class LIST>
YAML::Node writeYAMLOrder(
  const LIST<T>& content,
  const auto& Op = std::less<T>());

template <class K, class V, template<class> class MAP>
YAML::Node writeYAMLOrder(
  MAP<K, V>::const_iterator begin,
  MAP<K, V>::const_iterator end,
  const auto& Op = std::less<T>());

template <class K, class V, template<class> class LIST>
YAML::Node writeYAMLOrder(
  const MAP<K, V>& content,
  const auto& Op = std::less<T>());

//Definitions
template <class T>
YAML::Node writeYAMLSimple(const T& content)
{
  return YAML::Node(std::to_string(content));
}

template <class T>
YAML::Node writeYAMLPointer(T begin, T end)
{
  YAML::Node node;
  size_t count = 0;
  for(auto x = begin; x != end; ++x)
  {
    node[count] = writeYAML(*x);
    ++count;
  }
  return node;
}

template <class T1, class T2>
YAML::Node writeYAML(const std::pair<T1, T2>& content)
{
  YAML::Node node;
  node[0] = content.first;
  node[1] = content.second;
}

template <class T, template <class> class LIST>
YAML::Node writeYAMLList(const LIST<T>& content)
{
  return writeYAMLList(content.begin(), content.end());
}

template <class T, template <class> class LIST>
YAML::Node writeYAMLList(
  LIST<T>::const_iterator begin,
  LIST<T>::const_iterator end)
{
  YAML::Node node;
  size_t count = 0;
  for (auto x = begin; x != end; ++x)
  {
    node[count] = writeYAML(*x);
    ++count;
  }
  return node;
}

template <class K, class V, template<class> class MAP>
YAML::Node writeYAMLMap(const MAP<K, V>& content)
{
  return writeYAMLMap(content.begin(), content.end());
}

template <class K, class V, template<class> class MAP>
YAML::Node writeYAMLMap(
  MAP<K, V>::const_iterator begin,
  MAP<K, V>::const_iterator end)
{
  YAML::Node node;
  for (auto x = begin; x != end; ++x)
  {
    node[std::to_string(x->first)] = writeYAML(x->second);
  }
  return node;
}

template <class T, template<class> class LIST>
YAML::Node writeYAMLOrder(
  LIST<T>::const_iterator begin,
  LIST<T>::const_iterator end,
  const auto& Op)
{
  std::multiset<T, decltype(Op)> temp;
  std::copy(begin, end, inserter(temp));
  return writeYAML(temp);
}

template <class T, template<class> class LIST>
YAML::Node writeYAMLOrder(const LIST<T>& content, const auto& Op)
{
  return writeYAMLOrder(content.begin(), content.end(), Op);
}


template <class K, class V, template<class> class MAP>
YAML::Node writeYAMLOrder(
  MAP<K, V>::const_iterator begin,
  MAP<K, V>::const_iterator end,
  const auto& Op)
{
  std::multimap<K, V, decltype(Op)> temp;
  temp.insert(begin, end);
  return writeYAML(temp);
}

template <class K, class V, template<class> class MAP>
YAML::Node writeYAMLOrder(const MAP<K, V>& content, const auto& op)
{
  return writeYAML(content.begin(), content.end(), op);
}
#endif
