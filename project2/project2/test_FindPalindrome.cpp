#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

/* Provided test cases */

TEST_CASE("Test recursion", "[FindPalindrome]"){
	FindPalindrome b;
	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
	REQUIRE(b.number() == 6);
}

/* Your test cases here */

// Testing Add Function
TEST_CASE("add rejects non-alpha string", "[add]") {
	FindPalindrome a;
	REQUIRE_FALSE(a.add("&&&"));
}

TEST_CASE("add rejects empty string", "[add]") {
	FindPalindrome b;
	REQUIRE_FALSE(b.add(""));
}

TEST_CASE("add rejects duplicate word (case-insensitive)", "[add]") {
	FindPalindrome c;
	REQUIRE(c.add("fish"));
	REQUIRE_FALSE(c.add("Fish"));
	REQUIRE_FALSE(c.add("FISH"));
}