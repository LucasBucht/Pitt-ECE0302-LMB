#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Add.hpp"

/* Provided tests */

TEST_CASE("Test add", "[Add]"){

  Add<int> a;
  REQUIRE(a.call(1,2)==3);
}

/* Your tests here */

TEST_CASE("Test add 2", "[Add]"){

  Add<double> b;
  REQUIRE(b.call(1.0,2.0)==3.0);
}

TEST_CASE("Test add 3", "[Add]"){

  Add<bool> c;
  REQUIRE(c.call(true,false)==true);
}