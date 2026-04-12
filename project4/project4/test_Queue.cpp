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

TEST_CASE("Queue: peekFront returns first enqueued item", "[queue]") {
  Queue<int, List<int>> queue;
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);
  REQUIRE(queue.peekFront() == 1);
}

TEST_CASE("Queue: dequeue removes front item", "[queue]") {
  Queue<int, List<int>> queue;
  queue.enqueue(10);
  queue.enqueue(20);
  queue.enqueue(30);

  REQUIRE(queue.peekFront() == 10);
  queue.dequeue();
  REQUIRE(queue.peekFront() == 20);
  queue.dequeue();
  REQUIRE(queue.peekFront() == 30);
  queue.dequeue();
  REQUIRE(queue.isEmpty());
}

TEST_CASE("Queue: peekFront on empty queue throws", "[queue]") {
  Queue<int, List<int>> queue;
  REQUIRE_THROWS_AS(queue.peekFront(), std::out_of_range);
}

TEST_CASE("Queue: enqueue and dequeue many items", "[queue]") {
  Queue<int, List<int>> queue;
  for (int i = 0; i < 100; ++i) {
    queue.enqueue(i);
  }
  for (int i = 0; i < 100; ++i) {
    REQUIRE(queue.peekFront() == i);
    queue.dequeue();
  }
  REQUIRE(queue.isEmpty());
}

TEST_CASE("Queue: works with string type", "[queue]") {
  Queue<std::string, List<std::string>> queue;
  queue.enqueue("hello");
  queue.enqueue("world");
  REQUIRE(queue.peekFront() == "hello");
  queue.dequeue();
  REQUIRE(queue.peekFront() == "world");
}

TEST_CASE("Queue: peekFront does not remove item", "[queue]") {
  Queue<int, List<int>> queue;
  queue.enqueue(42);
  queue.peekFront();
  queue.peekFront();
  REQUIRE_FALSE(queue.isEmpty());
  REQUIRE(queue.peekFront() == 42);
}