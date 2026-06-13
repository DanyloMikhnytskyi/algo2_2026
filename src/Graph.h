#pragma once

#include <vector>
#include <utility>
#include <iostream>

// Represents a directed weighted edge
struct Edge {
    int from;
    int to;
    int weight;
};

// Graph representation type selector
enum class RepType { MATRIX, LIST };

// Abstract base class for a directed weighted graph
class Graph {
protected:
    int vertexCount;
    int edgeCount;

public:
    explicit Graph(int vertices)
        : vertexCount(vertices), edgeCount(0) {}

    virtual ~Graph() = default;

    // Add a directed edge from u to v with weight w
    virtual void addEdge(int u, int v, int w) = 0;

    // Get all neighbors of vertex v as (neighbor, weight) pairs
    virtual std::vector<std::pair<int, int>> getNeighbors(int v) const = 0;

    // Get the weight of edge (u -> v), returns INT_MAX if no edge exists
    virtual int getEdgeWeight(int u, int v) const = 0;

    // Get all edges in the graph
    virtual std::vector<Edge> getAllEdges() const = 0;

    // Print the graph in the file format to stdout
    virtual void print() const = 0;

    int getVertexCount() const { return vertexCount; }
    int getEdgeCount() const { return edgeCount; }
};
