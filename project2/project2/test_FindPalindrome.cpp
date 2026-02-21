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

TEST_CASE("add(vector) rejects duplicates with existing words", "[add]") {
	FindPalindrome c;
	REQUIRE(c.add("abc"));
	std::vector<std::string> v = {"def", "ABC"};
	REQUIRE_FALSE(c.add(v));
	REQUIRE(c.number() == 0);
}

TEST_CASE("add(vector) accepts valid unique words", "[add]") {
	FindPalindrome d;
	std::vector<std::string> v = {"Never", "Odd", "or", "Even"};
	REQUIRE(d.add(v));
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

// Testing toVector Function
TEST_CASE("toVector returns correct palindrome sentences", "[toVector]") {
	FindPalindrome a;
	a.add("a");
	a.add("AA");
	a.add("AaA");
	auto v = a.toVector();
	REQUIRE(v.size() == 6);
}

TEST_CASE("toVector is empty after clear", "[toVector]") {
	FindPalindrome b;
	b.add("kayak");
	b.clear();
	REQUIRE(b.toVector().empty());
}

// Testing CutTest1 Function
TEST_CASE("cutTest1 returns true when at most one odd count character", "[cutTest1]") {
	FindPalindrome a;
	REQUIRE(a.cutTest1({"aba"}));
	REQUIRE_FALSE(a.cutTest1({"ab"}));
	REQUIRE(a.cutTest1({"aa"}));
}

TEST_CASE("cutTest1 works across multiple words", "[cutTest1]") {
	FindPalindrome b;
	REQUIRE(b.cutTest1({"ab", "ba"}));
	REQUIRE(b.cutTest1({"abc", "ba"}));
	REQUIRE(b.cutTest1({"abc", "bc"}));
	REQUIRE_FALSE(b.cutTest1({"ab", "cd"}));
}