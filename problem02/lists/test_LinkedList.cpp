#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "LinkedList.hpp"
#include <stdexcept>

TEST_CASE("New list is empty", "[LinkedList]")
{
    LinkedList<int> list;

    REQUIRE(list.isEmpty());
    REQUIRE(list.getLength() == 0);
}

TEST_CASE("Insert elements preserves order", "[LinkedList]")
{
    LinkedList<int> list;

    list.insert(0, 10);
    list.insert(1, 30);
    list.insert(1, 20);

    REQUIRE(list.getLength() == 3);
    REQUIRE(list.getEntry(0) == 10);
    REQUIRE(list.getEntry(1) == 20);
    REQUIRE(list.getEntry(2) == 30);
}

TEST_CASE("Remove elements shifts list correctly", "[LinkedList]")
{
    LinkedList<int> list;

    list.insert(0, 1);
    list.insert(1, 2);
    list.insert(2, 3);

    list.remove(1);

    REQUIRE(list.getLength() == 2);
    REQUIRE(list.getEntry(0) == 1);
    REQUIRE(list.getEntry(1) == 3);
}

TEST_CASE("setEntry updates value", "[LinkedList]")
{
    LinkedList<int> list;

    list.insert(0, 5);
    list.setEntry(0, 42);

    REQUIRE(list.getEntry(0) == 42);
}

TEST_CASE("clear empties the list", "[LinkedList]")
{
    LinkedList<int> list;

    list.insert(0, 1);
    list.insert(1, 2);
    list.clear();

    REQUIRE(list.isEmpty());
    REQUIRE(list.getLength() == 0);
}

TEST_CASE("Out of range access throws exception", "[LinkedList]")
{
    LinkedList<int> list;

    REQUIRE_THROWS_AS(list.getEntry(0), std::out_of_range);
    REQUIRE_THROWS_AS(list.remove(0), std::out_of_range);
    REQUIRE_THROWS_AS(list.setEntry(0, 10), std::out_of_range);
    REQUIRE_THROWS_AS(list.insert(1, 5), std::out_of_range);
}

TEST_CASE("Copy constructor performs deep copy", "[LinkedList]")
{
    LinkedList<int> list;
    list.insert(0, 1);
    list.insert(1, 2);

    LinkedList<int> copy(list);
    copy.setEntry(0, 99);

    REQUIRE(list.getEntry(0) == 1);
    REQUIRE(copy.getEntry(0) == 99);
}

TEST_CASE("Copy assignment uses copy-swap safely", "[LinkedList]")
{
    LinkedList<int> a;
    a.insert(0, 1);
    a.insert(1, 2);

    LinkedList<int> b;
    b.insert(0, 10);

    b = a;
    b.setEntry(1, 99);

    REQUIRE(a.getEntry(1) == 2);
    REQUIRE(b.getEntry(1) == 99);
}
