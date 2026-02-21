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

TEST_CASE("add accepts valid unique words", "[add]") {
	FindPalindrome d;
	REQUIRE(d.add("Never"));
	REQUIRE(d.add("Odd"));
	REQUIRE(d.add("or"));
	REQUIRE(d.add("Even"));
}

// Testing Add(Vector) Function
TEST_CASE("add(vector) rejects if any word is invalid", "[add]") {
	FindPalindrome a;
	std::vector<std::string> v = {"hello", "world2", "test"};
	REQUIRE_FALSE(a.add(v));
	REQUIRE(a.number() == 0);
}

TEST_CASE("add(vector) rejects duplicates inside the vector", "[add]") {
	FindPalindrome b;
	std::vector<std::string> v = {"abc", "ABC"};
	REQUIRE_FALSE(b.add(v));
	REQUIRE(b.number() == 0);
}




// Testing Clear Function
TEST_CASE("clear resets palindromes", "[clear]") {
	FindPalindrome a;
	a.add("a");
	a.add("AA");
	a.add("AaA");
	REQUIRE(a.number() == 6);
	a.clear();
	REQUIRE(a.number() == 0);
}

TEST_CASE("words can be re-added after clear", "[clear]") {
	FindPalindrome b;
	b.add("b");
	b.add("BB");
	b.add("BbB");
	b.clear();
	REQUIRE(b.number() == 0);
	REQUIRE(b.add("b"));
}