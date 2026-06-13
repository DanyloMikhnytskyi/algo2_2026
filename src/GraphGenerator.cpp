#include "GraphGenerator.h"
#include "AdjMatrix.h"
#include "AdjList.h"
#include <random>
#include <algorithm>
#include <cmath>

std::unique_ptr<Graph> generateRandomGraph(int V,
                                            double density,
                                            RepType rep,
                                            bool allowNegative) {
    // Calculate number of edges
    long long maxEdges = static_cast<long long>(V) * (V - 1); // directed, no self-loops
    int E = static_cast<int>(std::round(density * maxEdges));
    if (E > maxEdges) E = static_cast<int>(maxEdges);
    if (E < 0) E = 0;

    // Build list of all possible directed edges (no self-loops)
    std::vector<std::pair<int, int>> allEdges;
    allEdges.reserve(maxEdges);
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (u != v) {
                allEdges.emplace_back(u, v);
            }
        }
    }

    // Shuffle and pick first E edges (Fisher-Yates via std::shuffle)
    static std::mt19937 rng(std::random_device{}());
    std::shuffle(allEdges.begin(), allEdges.end(), rng);

    // Create graph
    std::unique_ptr<Graph> graph;
    if (rep == RepType::MATRIX) {
        graph = std::make_unique<AdjMatrix>(V);
    } else {
        graph = std::make_unique<AdjList>(V);
    }

    // Weight distribution
    int wMin = allowNegative ? -50 : 1;
    int wMax = 100;
    std::uniform_int_distribution<int> weightDist(wMin, wMax);

    for (int i = 0; i < E; ++i) {
        int w = weightDist(rng);
        graph->addEdge(allEdges[i].first, allEdges[i].second, w);
    }

    return graph;
}
