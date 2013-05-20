 #include <UnitTest++.h>

  const int a = 100;

  int fact(int n) {
    if (n<0) return -1;
    else if (n==0) return 1;
    else return n * fact(n-1); 
  }

  TEST(fact) {
    CHECK_EQUAL(24,fact(4));
    CHECK_EQUAL(-1,fact(-100));
    CHECK_EQUAL(2,fact(2));
    CHECK_EQUAL(1,fact(0));
  }

  TEST(TooSimple) {
    CHECK_EQUAL(a,101);
  }

  int main() { 
    return UnitTest::RunAllTests();
  }
