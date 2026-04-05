#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "BinarySearchTree.hpp"

/* Provided test cases */

TEST_CASE("BST: Test Insert", "[insert]") {
    BinarySearchTree<int, int> bst1;

    REQUIRE(bst1.isEmpty());

    bst1.insert(10, 10);
    REQUIRE_FALSE(bst1.isEmpty());
}

TEST_CASE("BST: Test Duplicate Insert", "[duplicate insert]") {
    BinarySearchTree<int, int> bst1;
    
    REQUIRE(bst1.insert(12, 12));
    REQUIRE(!bst1.insert(12, 12));
}

TEST_CASE("BST: Test Remove With No Children", "[remove]") {
    BinarySearchTree<int, int> bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);

    int item;

    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(15, item));

    bst1.remove(5);
    REQUIRE_FALSE(bst1.retrieve(5, item));

    bst1.remove(15);
    REQUIRE_FALSE(bst1.retrieve(15, item));

    bst1.remove(10);
    REQUIRE_FALSE(bst1.retrieve(10, item));

    REQUIRE(bst1.isEmpty());
}

TEST_CASE("BST: Test Copy Assign", "[copy assign]") {
    BinarySearchTree<int, int> bst1;

    bst1.insert(50, 50);
    bst1.insert(0, 0);
    bst1.insert(100, 100);
    bst1.insert(25, 25);
    bst1.insert(75, 75);

    BinarySearchTree<int, int> bst2;

    bst2 = bst1;

    bst1.destroy();

    REQUIRE(bst1.isEmpty());

    REQUIRE_FALSE(bst2.isEmpty());

    int item;
    REQUIRE(bst2.retrieve(100, item));
    REQUIRE(bst2.retrieve(75, item));
    REQUIRE(bst2.retrieve(50, item));
    REQUIRE(bst2.retrieve(25, item));
    REQUIRE_FALSE(bst2.retrieve(51, item));
}

/* Your test cases here */

TEST_CASE("Remove root with one child", "[remove]") {
    BinarySearchTree<int, int> bst;
    bst.insert(10, 10);
    bst.insert(20, 20);

    int item;
    REQUIRE(bst.remove(10));
    REQUIRE_FALSE(bst.retrieve(10, item));
    REQUIRE(bst.retrieve(20, item));
}

TEST_CASE("Remove node with only left child", "[remove]") {
    BinarySearchTree<int, int> bst;
    bst.insert(10, 10);
    bst.insert(5, 5);
    bst.insert(3, 3);

    int item;
    REQUIRE(bst.remove(5));
    REQUIRE_FALSE(bst.retrieve(5, item));
    REQUIRE(bst.retrieve(3, item));
    REQUIRE(bst.retrieve(10, item));
}

TEST_CASE("Remove node with only right child", "[remove]") {
    BinarySearchTree<int, int> bst;
    bst.insert(10, 10);
    bst.insert(5, 5);
    bst.insert(7, 7);

    int item;
    REQUIRE(bst.remove(5));
    REQUIRE_FALSE(bst.retrieve(5, item));
    REQUIRE(bst.retrieve(7, item));
    REQUIRE(bst.retrieve(10, item));
}

TEST_CASE("Remove node with two children", "[remove]") {
    BinarySearchTree<int, int> bst;
    bst.insert(10, 10);
    bst.insert(5, 5);
    bst.insert(15, 15);
    bst.insert(12, 12);
    bst.insert(20, 20);

    int item;
    REQUIRE(bst.remove(15));
    REQUIRE_FALSE(bst.retrieve(15, item));
    REQUIRE(bst.retrieve(10, item));
    REQUIRE(bst.retrieve(5,  item));
    REQUIRE(bst.retrieve(12, item));
    REQUIRE(bst.retrieve(20, item));
}

TEST_CASE("Remove root with two children", "[remove]") {
    BinarySearchTree<int, int> bst;
    bst.insert(10, 10);
    bst.insert(5,  5);
    bst.insert(15, 15);

    int item;
    REQUIRE(bst.remove(10));
    REQUIRE_FALSE(bst.retrieve(10, item));
    REQUIRE(bst.retrieve(5,  item));
    REQUIRE(bst.retrieve(15, item));
    REQUIRE_FALSE(bst.isEmpty());
}

TEST_CASE("Remove key not in tree", "[remove]") {
    BinarySearchTree<int, int> bst;
    bst.insert(10, 10);

    REQUIRE_FALSE(bst.remove(99));
}
