#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "List.hpp"
#include "Queue.hpp"

/* Provided test cases */
TEST_CASE("Queue: Testing Enqueue", "[queue]") {

  Queue<int, List<int>> queue;

  REQUIRE(queue.isEmpty());
  queue.enqueue(12);
  REQUIRE_FALSE(queue.isEmpty());

}

/* Your test cases here */

TEST_CASE("Queue: isEmpty after all items dequeued", "[queue]") {
  Queue<int, List<int>> queue;
  queue.enqueue(5);
  queue.dequeue();
  REQUIRE(queue.isEmpty());
}

TEST_CASE("Queue: dequeue on empty queue throws", "[queue]") {
  Queue<int, List<int>> queue;
  REQUIRE_THROWS_AS(queue.dequeue(), std::out_of_range);
}