#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "DynamicBag.hpp"

TEST_CASE("Bag starts empty", "[DynamicBag]") {
  DynamicBag<int> bag;

  REQUIRE(bag.isEmpty());
  REQUIRE(bag.getCurrentSize() == 0);
}

TEST_CASE("Add items dynamically", "[DynamicBag]") {
  DynamicBag<int> bag;

  REQUIRE(bag.add(1));
  REQUIRE(bag.add(2));
  REQUIRE(bag.add(1));

  REQUIRE(bag.getCurrentSize() == 3);
  REQUIRE_FALSE(bag.isEmpty());
}

TEST_CASE("Frequency and contains", "[DynamicBag]") {
  DynamicBag<int> bag;

  bag.add(5);
  bag.add(5);
  bag.add(6);

  REQUIRE(bag.getFrequencyOf(5) == 2);
  REQUIRE(bag.getFrequencyOf(6) == 1);
  REQUIRE(bag.getFrequencyOf(7) == 0);

  REQUIRE(bag.contains(5));
  REQUIRE_FALSE(bag.contains(7));
}

TEST_CASE("Remove items dynamically", "[DynamicBag]") {
  DynamicBag<int> bag;

  bag.add(1);
  bag.add(2);
  bag.add(3);

  REQUIRE(bag.remove(2));
  REQUIRE(bag.getCurrentSize() == 2);
  REQUIRE_FALSE(bag.contains(2));

  REQUIRE_FALSE(bag.remove(42));
}

TEST_CASE("Clear removes all items", "[DynamicBag]") {
  DynamicBag<int> bag;

  bag.add(1);
  bag.add(2);

  bag.clear();

  REQUIRE(bag.isEmpty());
  REQUIRE(bag.getCurrentSize() == 0);
}

TEST_CASE("Copy constructor performs deep copy", "[DynamicBag]") {
  DynamicBag<int> bag1;
  bag1.add(1);
  bag1.add(2);

  DynamicBag<int> bag2 = bag1;

  REQUIRE(bag2.getCurrentSize() == 2);
  REQUIRE(bag2.contains(1));
  REQUIRE(bag2.contains(2));
}

TEST_CASE("Copy assignment performs deep copy", "[DynamicBag]") {
  DynamicBag<int> bag1;
  bag1.add(10);
  bag1.add(20);

  DynamicBag<int> bag2;
  bag2 = bag1;

  REQUIRE(bag2.getCurrentSize() == 2);
  REQUIRE(bag2.contains(10));
  REQUIRE(bag2.contains(20));
}
