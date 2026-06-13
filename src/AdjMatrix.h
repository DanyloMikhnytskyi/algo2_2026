#pragma once

#include "Graph.h"
#include <climits>

class AdjMatrix : public Graph {
private:
    std::vector<std::vector<int>> matrix;

public:
    explicit AdjMatrix(int vertices);

    void addEdge(int u, int v, int w) override;
    std::vector<std::pair<int, int>> getNeighbors(int v) const override;
    int getEdgeWeight(int u, int v) const override;
    std::vector<Edge> getAllEdges() const override;
    void print() const override;
};
