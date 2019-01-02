#ifndef TEST_COMMON_RWYAML_HPP
#define TEST_COMMON_RWYAML_HPP

#include "basic_functions.h"

class testdata {
public:
  bool dbool;
  YAML::Node nbool;
  double ddouble;
  YAML::Node ndouble;
  int64_t di64;
  YAML::Node ni64;
  uint64_t du64;
  YAML::Node du64;
  std::string dstring;
  YAML::Node nstring;
  vector<int> dvint;
  YAML::Node nvint;
  
  testdata ();
  virtual ~testdata ();
};

#endif
