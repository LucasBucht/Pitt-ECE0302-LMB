#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "List.hpp"
#include "sort.hpp"

/* Provided test cases */
TEST_CASE("Sort: Test move entry", "[sorting]") {
  List<int> lst;

  lst.insert(0, 100);
  lst.insert(1, 4);
  lst.insert(2, 10);
  lst.insert(3, 25);
  lst.insert(4, 11);

  // move forward
  lst.moveEntry(0, 2);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(0) == 4);
  REQUIRE(lst.getEntry(1) == 10);
  REQUIRE(lst.getEntry(2) == 100);
  REQUIRE(lst.getEntry(3) == 25);
  REQUIRE(lst.getEntry(4) == 11);

  // move backward
  lst.moveEntry(4, 0);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(0) == 11);
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 100);
  REQUIRE(lst.getEntry(4) == 25);

  // invalid moves
  REQUIRE_THROWS_AS(lst.moveEntry(5,0), std::out_of_range);
  REQUIRE_THROWS_AS(lst.moveEntry(0,5), std::out_of_range);
}


TEST_CASE("Sort: Integer sorting", "[sorting]"){

  List<int> lst;

  lst.insert(0, 100);
  lst.insert(1, 25);
  lst.insert(2, 10);
  lst.insert(3, 4);
  lst.insert(4, 11);

  quick_sort(lst, 0, lst.getLength()-1);

  // check sorted list
  REQUIRE(lst.getEntry(0) == 4);
  REQUIRE(lst.getEntry(1) == 10);
  REQUIRE(lst.getEntry(2) == 11);
  REQUIRE(lst.getEntry(3) == 25);
  REQUIRE(lst.getEntry(4) == 100);
}

TEST_CASE("Sort: Test partitioning", "[sorting]") {
    List<int> lst;
  
    lst.insert(0, 100);
    lst.insert(1, 30);
    lst.insert(2, 50);
    lst.insert(3, 4);
    lst.insert(4, 256);
    lst.insert(5, 1);
    lst.insert(6, 0);
    lst.insert(7, 25);
    lst.insert(8, 10);
    lst.insert(9, 512);
  
    // partition whole list
    int test = partition(lst, 0, lst.getLength()-1);
    // first item (100) should now be at index 7
    REQUIRE(test == 7);
}

/* Your test cases here */
TEST_CASE("Sort: Single element list", "[sorting]") {
  List<int> list1;
  list1.insert(0, 42);
  quick_sort(list1, 0, list1.getLength() - 1);
  REQUIRE(list1.getLength() == 1);
  REQUIRE(list1.getEntry(0) == 42);
}

TEST_CASE("Sort: Already sorted list", "[sorting]") {
  List<int> list2;
  list2.insert(0, 1);
  list2.insert(1, 2);
  list2.insert(2, 3);
  list2.insert(3, 4);
  list2.insert(4, 5);

  quick_sort(list2, 0, list2.getLength() - 1);

  REQUIRE(list2.getEntry(0) == 1);
  REQUIRE(list2.getEntry(1) == 2);
  REQUIRE(list2.getEntry(2) == 3);
  REQUIRE(list2.getEntry(3) == 4);
  REQUIRE(list2.getEntry(4) == 5);
}

TEST_CASE("Sort: Reverse sorted list", "[sorting]") {
  List<int> list3;
  list3.insert(0, 5);
  list3.insert(1, 4);
  list3.insert(2, 3);
  list3.insert(3, 2);
  list3.insert(4, 1);

  quick_sort(list3, 0, list3.getLength() - 1);

  for (int i = 0; i < 5; i++)
    REQUIRE(list3.getEntry(i) == i + 1);
}

TEST_CASE("Sort: Two element list", "[sorting]") {
  List<int> list4;
  list4.insert(0, 9);
  list4.insert(1, 3);

  quick_sort(list4, 0, list4.getLength() - 1);

  REQUIRE(list4.getEntry(0) == 3);
  REQUIRE(list4.getEntry(1) == 9);
}

TEST_CASE("Sort: Character sorting", "[sorting]") {
  List<char> list5;
  list5.insert(0, 'z');
  list5.insert(1, 'a');
  list5.insert(2, 'm');
  list5.insert(3, 'c');
  list5.insert(4, 'p');

  quick_sort(list5, 0, list5.getLength() - 1);

  REQUIRE(list5.getEntry(0) == 'a');
  REQUIRE(list5.getEntry(1) == 'c');
  REQUIRE(list5.getEntry(2) == 'm');
  REQUIRE(list5.getEntry(3) == 'p');
  REQUIRE(list5.getEntry(4) == 'z');
}

TEST_CASE("Sort: String sorting", "[sorting]") {
  List<std::string> list6;
  list6.insert(0, "banana");
  list6.insert(1, "apple");
  list6.insert(2, "mango");
  list6.insert(3, "cherry");
  list6.insert(4, "date");

  quick_sort(list6, 0, list6.getLength() - 1);

  REQUIRE(list6.getEntry(0) == "apple");
  REQUIRE(list6.getEntry(1) == "banana");
  REQUIRE(list6.getEntry(2) == "cherry");
  REQUIRE(list6.getEntry(3) == "date");
  REQUIRE(list6.getEntry(4) == "mango");
}

TEST_CASE("Sort: Large list of integers", "[sorting]") {
  List<int> list7;
  for (int i = 19; i >= 0; i--)
    list7.insert(0, i);

  quick_sort(list7, 0, list7.getLength() - 1);

  for (int i = 0; i < 20; i++)
    REQUIRE(list7.getEntry(i) == i);
}

TEST_CASE("Sort: moveEntry when from == to", "[sorting]") {
  List<int> list8;
  list8.insert(0, 7);
  list8.insert(1, 3);
  list8.insert(2, 5);

  list8.moveEntry(1, 1);

  REQUIRE(list8.getEntry(0) == 7);
  REQUIRE(list8.getEntry(1) == 3);
  REQUIRE(list8.getEntry(2) == 5);
}

TEST_CASE("Sort: Partial sub-list sort", "[sorting]") {
  List<int> list9;
  list9.insert(0, 1); 
  list9.insert(1, 50);
  list9.insert(2, 20);
  list9.insert(3, 40);
  list9.insert(4, 30);
  list9.insert(5, 99); 

  quick_sort(list9, 1, 4);

  REQUIRE(list9.getEntry(0) == 1); 
  REQUIRE(list9.getEntry(1) == 20);
  REQUIRE(list9.getEntry(2) == 30);
  REQUIRE(list9.getEntry(3) == 40);
  REQUIRE(list9.getEntry(4) == 50);
  REQUIRE(list9.getEntry(5) == 99);
}
