#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "LimitedSizeBag.hpp"

TEST_CASE("Bag starts empty", "[LimitedSizeBag]") {
  LimitedSizeBag<int> bag;

  REQUIRE(bag.isEmpty());
  REQUIRE(bag.getCurrentSize() == 0);
}

TEST_CASE("Add items to the bag", "[LimitedSizeBag]") {
  LimitedSizeBag<int> bag;

  REQUIRE(bag.add(10));
  REQUIRE(bag.add(20));
  REQUIRE(bag.add(10));

  REQUIRE_FALSE(bag.isEmpty());
  REQUIRE(bag.getCurrentSize() == 3);
}

TEST_CASE("Frequency and contains work correctly", "[LimitedSizeBag]") {
  LimitedSizeBag<int> bag;

  bag.add(1);
  bag.add(2);
  bag.add(1);
  bag.add(1);

  REQUIRE(bag.getFrequencyOf(1) == 3);
  REQUIRE(bag.getFrequencyOf(2) == 1);
  REQUIRE(bag.getFrequencyOf(3) == 0);

  REQUIRE(bag.contains(1));
  REQUIRE(bag.contains(2));
  REQUIRE_FALSE(bag.contains(3));
}

TEST_CASE("Remove items from the bag", "[LimitedSizeBag]") {
  LimitedSizeBag<int> bag;

  bag.add(5);
  bag.add(6);
  bag.add(5);

  REQUIRE(bag.remove(5));
  REQUIRE(bag.getCurrentSize() == 2);
  REQUIRE(bag.getFrequencyOf(5) == 1);

  REQUIRE_FALSE(bag.remove(42)); // item not present
}

TEST_CASE("Clear removes all items", "[LimitedSizeBag]") {
  LimitedSizeBag<int> bag;

  bag.add(1);
  bag.add(2);
  bag.add(3);

  bag.clear();

  REQUIRE(bag.isEmpty());
  REQUIRE(bag.getCurrentSize() == 0);
}

TEST_CASE("Bag does not exceed max size", "[LimitedSizeBag]") {
  LimitedSizeBag<int> bag;

  for (std::size_t i = 0; i < LimitedSizeBag<int>::maxsize; i++){
    REQUIRE(bag.add(static_cast<int>(i)));
  }

  REQUIRE(bag.getCurrentSize() == LimitedSizeBag<int>::maxsize);
  REQUIRE_FALSE(bag.add(999));
}