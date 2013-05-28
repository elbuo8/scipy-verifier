
#include "UnitTest++.h"
//Solutions
const int a = 100;


//Tests
TEST(TooSimple){CHECK_EQUAL(a,100);}


int main() {
  return UnitTest::RunAllTests();
}
