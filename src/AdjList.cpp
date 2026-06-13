#include "AdjList.h"

AdjList::AdjList(int vertices)
    : Graph(vertices)
    , adj(vertices)
{
}

void AdjList::addEdge(int u, int v, int w) {
    // Check if edge already exists and update it
    for (auto& [neighbor, weight] : adj[u]) {
        if (neighbor == v) {
            weight = w;
            return;
        }
    }
    adj[u].emplace_back(v, w);
    edgeCount++;
}

std::vector<std::pair<int, int>> AdjList::getNeighbors(int v) const {
    return adj[v];
}

int AdjList::getEdgeWeight(int u, int v) const {
    for (const auto& [neighbor, weight] : adj[u]) {
        if (neighbor == v) {
            return weight;
        }
    }
    return INT_MAX; // no edge
}

std::vector<Edge> AdjList::getAllEdges() const {
    std::vector<Edge> edges;
    edges.reserve(edgeCount);
    for (int i = 0; i < vertexCount; ++i) {
        for (const auto& [neighbor, weight] : adj[i]) {
            edges.push_back({i, neighbor, weight});
        }
    }
    return edges;
}

void AdjList::print() const {
    std::cout << vertexCount << " " << edgeCount << "\n";
    for (int i = 0; i < vertexCount; ++i) {
        for (const auto& [neighbor, weight] : adj[i]) {
            std::cout << i << " " << neighbor << " " << weight << "\n";
        }
    }
}
