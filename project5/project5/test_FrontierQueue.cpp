#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "FrontierQueue.hpp"

/* Provided test cases */
TEST_CASE("Simple push test", "[FrontierQueue]")
{
    FrontierQueue<int> fq;
    REQUIRE(fq.empty());

    fq.push(1, 0, 1);

    REQUIRE_FALSE(fq.empty());
    REQUIRE(fq.contains(1));
}

TEST_CASE("Simple contains test", "[FrontierQueue]")
{
    FrontierQueue<int> fq;

    REQUIRE_FALSE(fq.contains(1));
    REQUIRE_FALSE(fq.contains(2));

    fq.push(1, 1, 1);
    fq.push(2, 2, 2);

    REQUIRE(fq.contains(1));
    REQUIRE(fq.contains(2));
    REQUIRE_FALSE(fq.contains(3));
}

TEST_CASE("Simple pop test", "[FrontierQueue]")
{
    FrontierQueue<int> fq;
    
    fq.push(1, 1, 1);

    State<int> state = fq.pop();
    REQUIRE(state.getValue() == 1);
    REQUIRE(state.getPathCost() == 1);
    REQUIRE(state.getFCost() == 2);
    REQUIRE(fq.empty());
}

TEST_CASE("Simple replaceif test", "[FrontierQueue]")
{
    FrontierQueue<int> fq;

    fq.push(1, 100, 100);

    fq.replaceif(1, 1);
    State<int> state = fq.pop();
    REQUIRE(state.getValue() == 1);
    REQUIRE(state.getPathCost() == 1);
    REQUIRE(state.getFCost() == 101);
}


/* Your test cases here */

TEST_CASE("Pop returns min f-cost", "[FrontierQueue]")
{
    FrontierQueue<int> fq;
    fq.push(10, 5, 5); 
    fq.push(20, 1, 1); 
    fq.push(30, 3, 3);  

    State<int> s = fq.pop();
    REQUIRE(s.getValue() == 20);
    REQUIRE(s.getFCost() == 2);
}

TEST_CASE("Pop order is always ascending f-cost", "[FrontierQueue]")
{
    FrontierQueue<int> fq;
    fq.push(3, 3, 0);
    fq.push(1, 1, 0);
    fq.push(2, 2, 0);

    REQUIRE(fq.pop().getValue() == 1);
    REQUIRE(fq.pop().getValue() == 2);
    REQUIRE(fq.pop().getValue() == 3);
    REQUIRE(fq.empty());
}

TEST_CASE("replaceif does nothing when cost is not lower", "[FrontierQueue]")
{
    FrontierQueue<int> fq;
    fq.push(1, 5, 5);

    fq.replaceif(1, 10);
    State<int> s = fq.pop();
    REQUIRE(s.getPathCost() == 5);
    REQUIRE(s.getFCost() == 10);
}