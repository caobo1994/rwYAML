#include "test_common.h"

testdata::testdata()
{
  dbool = True;
  nbool = dbool;
  di64 = -3;
  ni64 = di64;
  du64 = 3;
  nu64 = du64;
  dstring = "test";
  nstring = dstring;
  dvint = {1, 2, 3};
  nvint[0] = 1;
  nvint[1] = 2;
  nvint[2] = 3;
}
