#include "AdjMatrix.h"

AdjMatrix::AdjMatrix(int vertices)
    : Graph(vertices)
    , matrix(vertices, std::vector<int>(vertices, INT_MAX))
{
}

void AdjMatrix::addEdge(int u, int v, int w) {
    if (matrix[u][v] == INT_MAX) {
        edgeCount++;
    }
    matrix[u][v] = w;
}

std::vector<std::pair<int, int>> AdjMatrix::getNeighbors(int v) const {
    std::vector<std::pair<int, int>> neighbors;
    for (int i = 0; i < vertexCount; ++i) {
        if (matrix[v][i] != INT_MAX) {
            neighbors.emplace_back(i, matrix[v][i]);
        }
    }
    return neighbors;
}

int AdjMatrix::getEdgeWeight(int u, int v) const {
    return matrix[u][v];
}

std::vector<Edge> AdjMatrix::getAllEdges() const {
    std::vector<Edge> edges;
    edges.reserve(edgeCount);
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < vertexCount; ++j) {
            if (matrix[i][j] != INT_MAX) {
                edges.push_back({i, j, matrix[i][j]});
            }
        }
    }
    return edges;
}

void AdjMatrix::print() const {
    std::cout << vertexCount << " " << edgeCount << "\n";
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < vertexCount; ++j) {
            if (matrix[i][j] != INT_MAX) {
                std::cout << i << " " << j << " " << matrix[i][j] << "\n";
            }
        }
    }
}
