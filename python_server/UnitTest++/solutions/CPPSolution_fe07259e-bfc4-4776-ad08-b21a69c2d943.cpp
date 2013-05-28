
#include "UnitTest++.h"
//Solutions
const int a = 101;

//Tests
TEST(TooSimple){CHECK_EQUAL(a,101);}

int main() {
  return UnitTest::RunAllTests();
}
