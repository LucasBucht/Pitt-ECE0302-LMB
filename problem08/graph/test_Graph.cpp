#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "Graph.hpp"

// Collect traversal output into a vector
static std::vector<int> traversalResult;
void collectInt(int& v) { traversalResult.push_back(v); }
 
static std::vector<std::string> traversalResultStr;
void collectStr(std::string& s) { traversalResultStr.push_back(s); }

/* Provided test cases */
TEST_CASE("Test Construction", "[construction]") {
  Graph<int>  g;
  REQUIRE(g.getNumVertices() == 0);
}

/* Your test cases here */

// Add
TEST_CASE("Add single edge creates two vertices", "[add]") {
    Graph<int> g;
    REQUIRE(g.add(1, 2) == true);
    REQUIRE(g.getNumVertices() == 2);
    REQUIRE(g.getNumEdges() == 1);
}
 
TEST_CASE("Add multiple edges", "[add]") {
    Graph<int> g;
    g.add(1, 2);
    g.add(2, 3);
    g.add(3, 4);
    REQUIRE(g.getNumVertices() == 4);
    REQUIRE(g.getNumEdges() == 3);
}
 
TEST_CASE("Duplicate edge is rejected", "[add]") {
    Graph<int> g;
    REQUIRE(g.add(1, 2) == true);
    REQUIRE(g.add(1, 2) == false);
    REQUIRE(g.add(2, 1) == false);
    REQUIRE(g.getNumEdges() == 1);
}
 
TEST_CASE("Self-loop is rejected", "[add]") {
    Graph<int> g;
    REQUIRE(g.add(1, 1) == false);
    REQUIRE(g.getNumVertices() == 0);
    REQUIRE(g.getNumEdges() == 0);
}
 
TEST_CASE("Add edge with string labels", "[add]") {
    Graph<std::string> g;
    REQUIRE(g.add("A", "B") == true);
    REQUIRE(g.getNumVertices() == 2);
    REQUIRE(g.getNumEdges() == 1);
}
 
TEST_CASE("Adding edge to existing vertices does not duplicate them", "[add]") {
    Graph<int> g;
    g.add(1, 2);
    g.add(1, 3);
    REQUIRE(g.getNumVertices() == 3);
    REQUIRE(g.getNumEdges() == 2);
}

// Remove
TEST_CASE("Remove existing edge", "[remove]") {
    Graph<int> g;
    g.add(1, 2);
    REQUIRE(g.remove(1, 2) == true);
    REQUIRE(g.getNumEdges() == 0);
    REQUIRE(g.getNumVertices() == 0);
}
 
TEST_CASE("Remove non-existent edge returns false", "[remove]") {
    Graph<int> g;
    g.add(1, 2);
    REQUIRE(g.remove(1, 3) == false);
    REQUIRE(g.remove(3, 4) == false);
}
 
TEST_CASE("Remove edge from reversed direction", "[remove]") {
    Graph<int> g;
    g.add(1, 2);
    REQUIRE(g.remove(2, 1) == true); 
    REQUIRE(g.getNumEdges() == 0);
}
 
TEST_CASE("Vertex with remaining edge stays after remove", "[remove]") {
    Graph<int> g;
    g.add(1, 2);
    g.add(2, 3);
    REQUIRE(g.remove(1, 2) == true);
    REQUIRE(g.getNumVertices() == 2);
    REQUIRE(g.getNumEdges() == 1);
}
 
TEST_CASE("Remove from empty graph returns false", "[remove]") {
    Graph<int> g;
    REQUIRE(g.remove(1, 2) == false);
}
 
TEST_CASE("Remove one of many edges from a vertex", "[remove]") {
    Graph<int> g;
    g.add(1, 2);
    g.add(1, 3);
    g.add(1, 4);
    REQUIRE(g.remove(1, 2) == true);
    REQUIRE(g.getNumVertices() == 3);
    REQUIRE(g.getNumEdges() == 2);
}

// Add and Remove
TEST_CASE("Add and remove multiple times", "[mixed]") {
    Graph<int> g;
    g.add(1, 2);
    g.add(2, 3);
    g.remove(1, 2);
    REQUIRE(g.getNumVertices() == 2);
    REQUIRE(g.getNumEdges() == 1);
    g.add(3, 4);
    REQUIRE(g.getNumEdges() == 2);
}
 
TEST_CASE("Graph empty after all edges removed", "[mixed]") {
    Graph<int> g;
    g.add(1, 2);
    g.remove(1, 2);
    REQUIRE(g.getNumVertices() == 0);
    REQUIRE(g.getNumEdges() == 0);
}