#include "Graph.hpp"

template <typename LabelType>
Graph<LabelType>::Graph() : numEdges(0) {}

template <typename LabelType> 
int Graph<LabelType>::getNumVertices() const {
    return static_cast<int>(adjList.size());
}

template <typename LabelType> 
int Graph<LabelType>::getNumEdges() const {
    return numEdges;
}
        
template <typename LabelType> 
bool Graph<LabelType>::add(LabelType start, LabelType end) { 
    if (start == end) {
        return false;
    }

    if (adjList.count(start) && adjList[start].count(end)) {
        return false;
    }

    adjList[start].insert(end);
    adjList[end].insert(start);
    numEdges++;
    return true;
}   

template <typename LabelType> 
bool Graph<LabelType>::remove(LabelType start, LabelType end) {
  if (!adjList.count(start) || !adjList[start].count(end)) {
        return false;
    }

    adjList[start].erase(end);
    adjList[end].erase(start);
    --numEdges;

    if (adjList[start].empty()) {
        adjList.erase(start);
    }
    if (adjList.count(end) && adjList[end].empty()) {
        adjList.erase(end);
    }

    return true;
}

template <typename LabelType> 
void Graph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {
    // BONUS
}

template <typename LabelType> 
void Graph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {
    // BONUS
}