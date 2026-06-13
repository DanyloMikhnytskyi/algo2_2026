#include "FileIO.h"
#include "AdjMatrix.h"
#include "AdjList.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

std::unique_ptr<Graph> readGraphFromFile(const std::string& filename,
                                          RepType rep,
                                          int& startVertex) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    int V, E;
    file >> V >> E;

    if (V <= 0) {
        throw std::runtime_error("Invalid vertex count: " + std::to_string(V));
    }

    std::unique_ptr<Graph> graph;
    if (rep == RepType::MATRIX) {
        graph = std::make_unique<AdjMatrix>(V);
    } else {
        graph = std::make_unique<AdjList>(V);
    }

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        file >> u >> v >> w;
        if (u < 0 || u >= V || v < 0 || v >= V) {
            throw std::runtime_error("Edge vertex out of range: " +
                                     std::to_string(u) + " -> " + std::to_string(v));
        }
        graph->addEdge(u, v, w);
    }

    file >> startVertex;
    if (startVertex < 0 || startVertex >= V) {
        throw std::runtime_error("Start vertex out of range: " +
                                 std::to_string(startVertex));
    }

    return graph;
}

void printGraph(const Graph& g) {
    g.print();
}
