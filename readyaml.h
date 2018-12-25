/*
Copyright information needed.
Best decided by author of the whole library.
*/

/*
Passed with standard c++14, c++17 and compiler gcc-7.3.0
*/

#ifndef READYAML_CAOBO1994_H
#define READYAML_CAOBO1994_H

#include <cstdint>

#include <yaml-cpp/yaml.h>

#include <algorithm>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <string>

#include <exception>

// Definitions

/*
Appends new error information to the error information
 of an old std::append_logic_error
object to produce and return a new std::logic_error object.
*/
std::logic_error append_logic_error(
    const std::logic_error& old_exception,
    const std::string& new_content) throw();

/*
A general template to read object from a YAML::Node object.
source: the YAML::Node object where we read from.
dest: the object we get by reading and parsing source.
*/
template <class T>
size_t readYAMLObj(const YAML::Node& source, T& dest);

/*
A general template to read and append objects from
a YAML::Node object to the existing object.
source: the YAML::Node object where we read from.
dest: the object we expand by reading and parsing source.
*/
template <class T>
size_t appendYAMLObj(const YAML::Node& source, T& dest);

/*
A general template to read object from an iterator
pointing to a YAML::Node object.
source_ptr: Iterator pointing to a YAML::Node object where we read from.
dest: the object we get by reading and parsing source.
*/
template <class T>
size_t readYAMLObj(YAML::const_iterator& source_ptr, T& dest) {
  return readYAMLObj(*source_ptr, dest);
}

/*
A general template to read and append objects from an iterator
pointing to a YAML::Node object to the existing object.
source_ptr: Iterator pointing to a YAML::Node object where we read from.
dest: the object we expand by reading and parsing source.
*/
template <class T>
size_t appendYAMLObj(YAML::const_iterator& source_ptr, T& dest) {
  return appendYAMLObj(*source_ptr, dest);
}

/*
A general template to read object from a pair of iterators
enclosing to a series of YAML::Node object.
begin, end: Iterators enclosing a series of YAML::Node objects
where we read from.
dest: the object we get by reading and parsing source.
*/
template <class T>
size_t readYAMLObjRange(YAML::const_iterator begin, YAML::const_iterator end,
                        T& dest);

/*
A general template to read and append objects from a pair of iterators
enclosing to a series of YAML::Node object to the existing object.
begin, end: Iterators enclosing a series of YAML::Node objects
where we read from.
dest: the object we expand by reading and parsing source.
*/
template <class T>
size_t appendYAMLObjRange(YAML::const_iterator begin, YAML::const_iterator end,
                          T& dest);

/*
A template to read simple object from a YAML::Node Scalar object.
A simple object is an object whose type can be the argument type T
of function YAML::Node::as<T>();
source: the YAML::Node object where we read from.
dest: the object we get by reading and parsing source.
*/
template <class T>
size_t readYAMLObjScalar(const YAML::Node& source, T& dest);

/*
A template to read std::pair object from a YAML::Node Sequence object.
The size of the Sequence shall at least be 2,
otherwise, std::logic_error-type exception will be thrown.
source: the YAML::Node object where we read from.
dest: the object we get by reading and parsing source.
*/
template <class T0, class T1> /* pair */
size_t readYAMLObj(const YAML::Node& source, std::pair<T0, T1>& dest);

/*
A template to read std::pair object from two YAML::Node objects
 starting by an iterator.
Users shall ensure that there are at least 2 objects to be read.
begin: the iterator pointing to the YAML::Node object
where we first read from.
dest: the object we get by reading and parsing source.
*/
template <class T0, class T1>
size_t readYAMLObjRange(YAML::const_iterator begin, std::pair<T0, T1>& dest);

/*
A template to read object from a series of YAML objects
enclosed by a pair of iterators and insert to an insert_iterator.
begin, end: Iterators enclosing a series of YAML::Node objects
where we read from.
inserter: the insert_iterator used to insert elements to a containter.
*/
template <class T, class INSERTER>
size_t appendYAMLObjInserter(YAML::const_iterator begin,
                             YAML::const_iterator end, INSERTER inserter);

/*
A template to read from a Sequence-type YAML::Node object
and insert to an insert_iterator.
source: a Sequence-type YAML::Node object where we read from.
inserter: the insert_iterator used to insert elements to a containter.
*/
template <class T, class INSERTER>
size_t appendYAMLObjInserter(const YAML::Node& source, INSERTER inserter);

/*
From now on, the list-like containers are defined as containers
with back_insert_iterator.
They currently include the containers with the following types:
std::vector, std::deque, std::list, std::forward_list
*/

/*
A template to read from a series of YAML objects
enclosed by a pair of iterators and append to a list-like containter.
begin, end: Iterators enclosing a series of YAML::Node objects
where we read from.
dest: the container that we append to.
*/
template <class T, class LIST>
size_t appendYAMLObjRangeList(YAML::const_iterator begin,
                              YAML::const_iterator end, LIST& dest);

/*
A template to read object from a series of YAML objects
enclosed by a pair of iterators to a list-like containter.
begin, end: Iterators enclosing a series of YAML::Node objects
where we read from.
dest: the container that we read to.
*/
template <class T, class LIST>
size_t readYAMLObjRangeList(YAML::const_iterator begin,
                            YAML::const_iterator end, LIST& dest);

/*
A template to read object from a Sequence-type YAML::Node object
to a list-like containter.
source: a Sequence-type YAML::Node object where we read from.
dest: the container that we read to.
*/
template <class T, class LIST>
size_t readYAMLObjList(const YAML::Node& source, LIST& dest);

/*
A template to read from a Sequence-type YAML::Node object
and append to a list-like containter.
source: a Sequence-type YAML::Node object where we read from.
dest: the container that we append to.
*/
template <class T, class LIST>
size_t appendYAMLObjList(const YAML::Node& source, LIST& dest);

/*
Realize appendYAMLObjRange, readYAMLObjRange, readYAMLObj, appendYAMLObj
for all list-like container types.
*/
#define LISTOP(LIST)                                                   \
  template <class T>                                                   \
  size_t appendYAMLObjRange(YAML::const_iterator begin,                \
                            YAML::const_iterator end, LIST<T>& dest) { \
    return appendYAMLObjRangeList<T>(begin, end, dest);                \
  }                                                                    \
  template <class T>                                                   \
  size_t readYAMLObjRange(YAML::const_iterator begin,                  \
                          YAML::const_iterator end, LIST<T>& dest) {   \
    return readYAMLObjRangeList<T>(begin, end, dest);                  \
  }                                                                    \
  template <class T>                                                   \
  size_t readYAMLObj(const YAML::Node& source, LIST<T>& dest) {        \
    return readYAMLObjList<T>(source, dest);                           \
  }                                                                    \
  template <class T>                                                   \
  size_t appendYAMLObj(const YAML::Node& source, LIST<T>& dest) {      \
    return appendYAMLObjList<T>(source, dest);                         \
  }

LISTOP(std::vector)
LISTOP(std::deque)
LISTOP(std::forward_list)
LISTOP(std::list)
#undef LISTOP

/*
From now on, the set-like containers are defined as containers
with insert_iterator.
They currently include the containers with the following types:
std::set, std::multiset, std::unordered_set, std::unordered_multiset
*/

/*
All the functions for set-like containters are defined the same way
as the functions for list-like containers.
*/
template <class T, class SET>
size_t appendYAMLObjRangeSet(YAML::const_iterator begin,
                             YAML::const_iterator end, SET& dest);

template <class T, class SET>
size_t readYAMLObjRangeSet(YAML::const_iterator begin, YAML::const_iterator end,
                           SET& dest);

template <class T, class SET>
size_t readYAMLObjSet(const YAML::Node& source, SET& dest);

template <class T, class SET>
size_t appendYAMLObjSet(const YAML::Node& source, SET& dest);

#define SETOP(SET)                                                          \
  template <class T>                                                        \
  size_t appendYAMLObjRange(const YAML::const_iterator begin,               \
                            const YAML::const_iterator end, SET<T>& dest) { \
    return appendYAMLObjRangeSet<T>(begin, end, dest);                      \
  }                                                                         \
  template <class T>                                                        \
  size_t readYAMLObjRange(const YAML::const_iterator begin,                 \
                          const YAML::const_iterator end, SET<T>& dest) {   \
    return readYAMLObjRangeSet<T>(begin, end, dest);                        \
  }                                                                         \
  template <class T>                                                        \
  size_t readYAMLObj(const YAML::Node& source, SET<T>& dest) {              \
    return readYAMLObjSet<T>(source, dest);                                 \
  }                                                                         \
  template <class T>                                                        \
  size_t appendYAMLObj(const YAML::Node& source, SET<T>& dest) {            \
    return appendYAMLObjSet<T>(source, dest);                               \
  }

SETOP(std::set)
SETOP(std::multiset)
SETOP(std::unordered_set)
SETOP(std::unordered_multiset)
#undef SETOP

/*
From now on, the map-like containers are defined as containers
that have key-value relationships.
They currently include the containers with the following types:
std::map, std::multimap, std::unordered_map, std::unordered_multimap
*/

/*
All the functions for map-like containters are defined the same way
as the functions for list-like containers.
*/

template <class K, class V, class MAP>
size_t appendYAMLObjRangeMap(YAML::const_iterator begin,
                             YAML::const_iterator end, MAP& dest);

template <class K, class V, class MAP>
size_t readYAMLObjRangeMap(YAML::const_iterator begin, YAML::const_iterator end,
                           MAP& dest);

template <class K, class V, class MAP>
size_t readYAMLObjMap(const YAML::Node& source, MAP& dest);

template <class K, class V, class MAP>
size_t appendYAMLObjMap(const YAML::Node& source, MAP& dest);

#define MAPOP(MAP)                                                       \
  template <class K, class V>                                            \
  size_t appendYAMLObjRange(YAML::const_iterator begin,                  \
                            YAML::const_iterator end, MAP<K, V>& dest) { \
    return appendYAMLObjRangeMap<K, V>(begin, end, dest);                \
  }                                                                      \
  template <class K, class V>                                            \
  size_t readYAMLObjRange(YAML::const_iterator begin,                    \
                          YAML::const_iterator end, MAP<K, V>& dest) {   \
    return readYAMLObjRangeMap<K, V>(begin, end, dest);                  \
  }                                                                      \
  template <class K, class V>                                            \
  size_t readYAMLObj(const YAML::Node& source, MAP<K, V>& dest) {        \
    return readYAMLObjMap<K, V>(source, dest);                           \
  }                                                                      \
  template <class K, class V>                                            \
  size_t appendYAMLObj(const YAML::Node& source, MAP<K, V>& dest) {      \
    return appendYAMLObjMap<K, V>(source, dest);                         \
  }

MAPOP(std::map)
MAPOP(std::multimap)
MAPOP(std::unordered_map)
MAPOP(std::unordered_multimap)
#undef MAPOP

// Template declarations
template <class T>
size_t readYAMLObjScalar(const YAML::Node& source, T& dest) {
  switch (source.Type()) {
    case YAML::NodeType::Null:
      dest = T();
      return 1;
    case YAML::NodeType::Scalar:
      dest = source.as<T>();
      return 1;
    case YAML::NodeType::Sequence:
      throw std::logic_error("No YAML Sequence for scalar type! ");
      return 0;
    case YAML::NodeType::Map:
      throw std::logic_error("No YAML Map for scalar type! ");
      return 0;
    default:
      throw std::logic_error("Unknown YAML type! ");
      return 0;
  }
}

template <class T0, class T1> /* pair */
size_t readYAMLObj(const YAML::Node& source, std::pair<T0, T1>& dest) {
  T0 e0;
  T1 e1;
  switch (source.Type()) {
    case YAML::NodeType::Null:
      throw std::logic_error("No YAML Null for pair! ");
      return 0;
    case YAML::NodeType::Scalar:
      throw std::logic_error("No YAML Scalar for pair! ");
      return 0;
    case YAML::NodeType::Sequence:
      if (source.size() < 2) {
        throw std::logic_error("Wrong size for pair! ");
        return 0;
      }
      try {
        readYAMLObj(source[0], e0);
      } catch (std::logic_error exception) {
        throw append_logic_error(exception,
                                 "Cannot read first element of pair! ");
        return 0;
      }
      try {
        readYAMLObj(source[1], e1);
      } catch (std::logic_error exception) {
        throw append_logic_error(exception,
                                 "Cannot read second element of pair! ");
        return 0;
      }
      dest.first = e0;
      dest.second = e1;
      return 2;
    case YAML::NodeType::Map:
      throw std::logic_error("No YAML Map for pair! ");
      return 0;
    default:
      throw std::logic_error("Unknown YAML type! ");
      return 0;
  }
  return 0;
}

template <class T0, class T1>
size_t readYAMLObjRange(YAML::const_iterator begin, std::pair<T0, T1>& dest) {
  T0 e0;
  T1 e1;
  auto first = begin;
  auto second = begin;
  ++second;
  try {
    readYAMLObj(first, e0);
  } catch (std::logic_error exception) {
    throw append_logic_error(exception, "Cannot read first element of pair! ");
    return 0;
  }
  try {
    readYAMLObj(second, e1);
  } catch (std::logic_error exception) {
    throw append_logic_error(exception, "Cannot read second element of pair! ");
    return 0;
  }
  dest.first = e0;
  dest.second = e1;
  return 2;
}

template <class T, class INSERTER>
size_t appendYAMLObjInserter(YAML::const_iterator begin,
                             YAML::const_iterator end, INSERTER inserter) {
  size_t count = 0;
  T element;
  for (auto x = begin; x != end; ++x) {
    try {
      readYAMLObj<T>(x, element);
    } catch (std::logic_error exception) {
      std::string new_content =
          "Cannot read #" + std::to_string(count) + " element! ";
      throw append_logic_error(exception, new_content);
      return count;
    }
    inserter = element;
  }
  return count;
}

template <class T, class INSERTER>
size_t appendYAMLObjInserter(const YAML::Node& source, INSERTER inserter) {
  return appendYAMLObjInserter<T>(source.begin(), source.end(), inserter);
}

template <class T, class LIST>
size_t appendYAMLObjRangeList(YAML::const_iterator begin,
                              YAML::const_iterator end, LIST& dest) {
  return appendYAMLObjInserter<T>(begin, end, back_inserter(dest));
}

template <class T, class LIST>
size_t readYAMLObjRangeList(YAML::const_iterator begin,
                            YAML::const_iterator end, LIST& dest) {
  dest.clear();
  return appendYAMLObjRangeList<T>(begin, end, dest);
}

template <class T, class LIST>
size_t readYAMLObjList(const YAML::Node& source, LIST& dest) {
  dest.clear();
  T element;
  switch (source.Type()) {
    case YAML::NodeType::Null:
      return 0;
    case YAML::NodeType::Scalar:
      try {
        readYAMLObj<T>(source, element);
      } catch (std::logic_error exception) {
        throw exception;
        return 0;
      }
      dest.emplace_back(element);
      return 1;
    case YAML::NodeType::Sequence:
      return readYAMLObjRangeList<T>(source.begin(), source.end(), dest);
    case YAML::NodeType::Map:
      throw std::logic_error("No YAML Map for List! ");
      return 0;
    default:
      throw std::logic_error("Unknown YAML type! ");
      return 0;
  }
  return 0;
}

template <class T, class LIST>
size_t appendYAMLObjList(const YAML::Node& source, LIST& dest) {
  LIST newlist;
  size_t count;
  try {
    count = readYAMLObjList<T>(source, newlist);
  } catch (std::logic_error exception) {
    throw exception;
    return 0;
  }
  dest.insert(dest.end(), newlist.begin(), newlist.end());
  return count;
}

template <class T, class SET>
size_t appendYAMLObjRangeSet(YAML::const_iterator begin,
                             YAML::const_iterator end, SET& dest) {
  return appendYAMLObjInserter<T>(begin, end, inserter(dest, dest.end()));
}

template <class T, class SET>
size_t readYAMLObjRangeSet(YAML::const_iterator begin, YAML::const_iterator end,
                           SET& dest) {
  dest.clear();
  return appendYAMLObjRangeSet<T>(begin, end, dest);
}

template <class T, class SET>
size_t readYAMLObjSet(const YAML::Node& source, SET& dest) {
  dest.clear();
  T element;
  switch (source.Type()) {
    case YAML::NodeType::Null:
      return 0;
    case YAML::NodeType::Scalar:
      try {
        readYAMLObj<T>(source, element);
      } catch (std::logic_error exception) {
        throw exception;
        return 0;
      }
      dest.emplace_back(element);
      return 1;
    case YAML::NodeType::Sequence:
      return readYAMLObjRangeList<T>(source.begin(), source.end(), dest);
    case YAML::NodeType::Map:
      throw std::logic_error("No YAML Map for set! ");
      return 0;
    default:
      throw std::logic_error("Unknown YAML type! ");
      return 0;
  }
  return 0;
}

template <class T, class SET>
size_t appendYAMLObjSet(const YAML::Node& source, SET& dest) {
  size_t count = 0;
  SET newset;
  try {
    count = readYAMLObjSet<T>(source, newset);
  } catch (std::logic_error exception) {
    throw exception;
  }
  dest.insert(newset.begin(), newset.end());
  return count;
}

template <class K, class V, class MAP>
size_t appendYAMLObjRangeMap(YAML::const_iterator begin,
                             YAML::const_iterator end, MAP& dest) {
  K key;
  V value;
  size_t count = 0;
  for (auto x = begin; x != end; ++x) {
    try {
      readYAMLObj(x->first, key);
    } catch (std::logic_error exception) {
      std::string new_content =
          "Cannot read key of #" + std::to_string(count) + " element! ";
      throw append_logic_error(exception, new_content);
      return count;
    }
    try {
      readYAMLObj(x->second, value);
    } catch (std::logic_error exception) {
      std::string new_content =
          "Cannot read value of #" + std::to_string(count) + " element! ";
      throw append_logic_error(exception, new_content);
      return count;
    }
    if (dest.find(key) != dest.end()) {
      throw std::logic_error("Duplicate keys " + std::to_string(key) + " ! ");
      return count;
    } else {
      dest.emplace(key, value);
    }
    ++count;
  }
  return count;
}

template <class K, class V, class MAP>
size_t readYAMLObjRangeMap(YAML::const_iterator begin, YAML::const_iterator end,
                           MAP& dest) {
  dest.clear();
  return readYAMLObjRangeMap<K, V>(begin, end, dest);
}

template <class K, class V, class MAP>
size_t readYAMLObjMap(const YAML::Node& source, MAP& dest) {
  dest.clear();
  switch (source.Type()) {
    case YAML::NodeType::Null:
      return 0;
    case YAML::NodeType::Scalar:
      throw std::logic_error("No YAML Scalar for unordered_map! ");
      return 0;
    case YAML::NodeType::Sequence:
      throw std::logic_error("No YAML Sequence for unordered_map! ");
      return 0;
    case YAML::NodeType::Map:
      return readYAMLObjRangeMap<K, V>(source.begin(), source.end(), dest);
    default:
      throw std::logic_error("Unknown YAML type! ");
      return 0;
  }
  return 0;
}

template <class K, class V, class MAP>
size_t appendYAMLObjMap(const YAML::Node& source, MAP& dest) {
  MAP newmap;
  size_t count;
  try {
    count = readYAMLObjMap<K, V>(source, newmap);
  } catch (std::logic_error exception) {
    throw exception;
    return 0;
  }
  dest.insert(newmap.begin(), newmap.end());
  return count;
}

#endif
