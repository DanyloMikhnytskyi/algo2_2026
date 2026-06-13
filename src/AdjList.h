#pragma once

#include "Graph.h"
#include <climits>

class AdjList : public Graph {
private:
    // adj[v] = list of (neighbor, weight) pairs for vertex v
    std::vector<std::vector<std::pair<int, int>>> adj;

public:
    explicit AdjList(int vertices);

    void addEdge(int u, int v, int w) override;
    std::vector<std::pair<int, int>> getNeighbors(int v) const override;
    int getEdgeWeight(int u, int v) const override;
    std::vector<Edge> getAllEdges() const override;
    void print() const override;
};
