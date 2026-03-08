#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "SortedList.hpp"
#include "List.hpp"

/* Provided tests */
TEST_CASE("SortedList: Testing size", "[sorted list]") {
  SortedList<char> lst;

  REQUIRE(lst.isEmpty());
  REQUIRE(lst.getLength() == 0);

  lst.insert('b');
  REQUIRE(!lst.isEmpty());
  REQUIRE(lst.getLength() == 1);

  lst.insert('a');
  REQUIRE(lst.getLength() == 2);

  lst.removeAt(0);
  REQUIRE(lst.getLength() == 1);

  lst.removeAt(0);
  REQUIRE(lst.getLength() == 0);
  REQUIRE(lst.isEmpty());
}


TEST_CASE("SortedList: Testing insert", "[sorted list]") {
  SortedList<char> lst;

  char c = 'a';
  while (c <= 'z') {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 26);

  bool getEntryCheck;
  for (int i = 0; i < 26; ++i) {
    getEntryCheck = (lst.getEntry(i) == 'a' + i);
    if (!getEntryCheck) {
      break;
    }
  }
  REQUIRE(getEntryCheck);
}


TEST_CASE("SortedList: Testing remove", "[sorted list]") {
  SortedList<char> lst;

  char c = 'a';
  int size = 10;
  while (c < 'a'+size) {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == size);

  lst.remove('c');
  REQUIRE(lst.getLength() == size-1);
  REQUIRE(lst.getEntry(2) == 'd');

  lst.remove('e');
  REQUIRE(lst.getLength() == size-2);
  REQUIRE(lst.getEntry(5) == 'h');

  lst.remove('a');
  REQUIRE(lst.getLength() == size-3);
  REQUIRE(lst.getEntry(0) == 'b');
}


TEST_CASE("SortedList: Testing getPosition", "[sorted list]") {
  SortedList<char> lst;
  
  lst.insert('a');
  lst.insert('d');
  lst.insert('e');
  lst.insert('c');
  lst.insert('b');

  REQUIRE(lst.getPosition('a') == 0);
  REQUIRE(lst.getPosition('b') == 1);
  REQUIRE(lst.getPosition('c') == 2);
  REQUIRE(lst.getPosition('d') == 3);
  REQUIRE(lst.getPosition('e') == 4);
}


TEST_CASE("Testing init from list", "[sorted list]") {
  List<char> unsorted;
  
  unsorted.insert(0,'a');
  unsorted.insert(1,'d');
  unsorted.insert(2,'e');
  unsorted.insert(3,'c');
  unsorted.insert(4,'b');

  SortedList<char> sorted(unsorted);

  REQUIRE(sorted.getPosition('a') == 0);
  REQUIRE(sorted.getPosition('b') == 1);
  REQUIRE(sorted.getPosition('c') == 2);
  REQUIRE(sorted.getPosition('d') == 3);
  REQUIRE(sorted.getPosition('e') == 4);
}

/* Your tests here */

TEST_CASE("SortedList: insert integers in reverse order stays sorted", "[sorted list]") {
  SortedList<int> lst;
  for (int i = 10; i >= 1; --i) lst.insert(i);
  REQUIRE(lst.getLength() == 10);
  for (int i = 0; i < 10; ++i)
    REQUIRE(lst.getEntry(i) == i + 1);
}

TEST_CASE("SortedList: duplicates are allowed and appear consecutively", "[sorted list]") {
  SortedList<int> lst;
  lst.insert(3); lst.insert(1); lst.insert(3); lst.insert(2); lst.insert(3);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(0) == 1);
  REQUIRE(lst.getEntry(1) == 2);
  REQUIRE(lst.getEntry(2) == 3);
  REQUIRE(lst.getEntry(3) == 3);
  REQUIRE(lst.getEntry(4) == 3);
}

TEST_CASE("SortedList: remove deletes only the first occurrence of a duplicate", "[sorted list]") {
  SortedList<int> lst;
  lst.insert(5); lst.insert(5); lst.insert(5);
  REQUIRE(lst.getLength() == 3);

  lst.remove(5);
  REQUIRE(lst.getLength() == 2);
  REQUIRE(lst.getEntry(0) == 5);
  REQUIRE(lst.getEntry(1) == 5);
}

TEST_CASE("SortedList: remove throws invalid_argument for missing item", "[sorted list]") {
  SortedList<int> lst;
  lst.insert(1); lst.insert(2); lst.insert(3);

  REQUIRE_THROWS_AS(lst.remove(42), std::invalid_argument);
}

TEST_CASE("SortedList: getPosition throws invalid_argument for missing item", "[sorted list]") {
  SortedList<char> lst;
  lst.insert('x');

  REQUIRE_THROWS_AS(lst.getPosition('z'), std::invalid_argument);
}

TEST_CASE("SortedList: removeAt throws out_of_range for bad index", "[sorted list]") {
  SortedList<int> lst;
  lst.insert(1);

  REQUIRE_THROWS_AS(lst.removeAt(5), std::out_of_range);
}

TEST_CASE("SortedList: clear empties the list", "[sorted list]") {
  SortedList<int> lst;
  lst.insert(1); lst.insert(2); lst.insert(3);
  lst.clear();

  REQUIRE(lst.isEmpty());
  REQUIRE(lst.getLength() == 0);
}

TEST_CASE("SortedList: copy constructor produces independent copy", "[sorted list]") {
  SortedList<int> original;
  original.insert(3); original.insert(1); original.insert(2);

  SortedList<int> copy(original);
  copy.insert(0);

  // original unchanged
  REQUIRE(original.getLength() == 3);
  REQUIRE(original.getEntry(0) == 1);

  // copy has extra element
  REQUIRE(copy.getLength() == 4);
  REQUIRE(copy.getEntry(0) == 0);
}

TEST_CASE("SortedList: assignment operator produces independent copy", "[sorted list]") {
  SortedList<int> a, b;
  a.insert(10); a.insert(20);
  b = a;
  b.insert(15);

  REQUIRE(a.getLength() == 2);
  REQUIRE(b.getLength() == 3);
  REQUIRE(b.getEntry(1) == 15);
}

TEST_CASE("SortedList: single element insert and remove", "[sorted list]") {
  SortedList<int> lst;
  lst.insert(42);
  REQUIRE(lst.getLength() == 1);
  REQUIRE(lst.getEntry(0) == 42);
  lst.remove(42);
  REQUIRE(lst.isEmpty());
}