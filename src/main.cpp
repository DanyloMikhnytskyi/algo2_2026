#include <iostream>
#include <string>
#include <memory>
#include <climits>
#include <filesystem>

#include "Graph.h"
#include "AdjMatrix.h"
#include "AdjList.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include "FileIO.h"
#include "GraphGenerator.h"
#include "Benchmark.h"
#include "ShortestPathResult.h"

// ─── Helpers ────────────────────────────────────────────────

static void printSeparator() {
    std::cout << "────────────────────────────────────────\n";
}

static RepType chooseRepresentation() {
    std::cout << "\nChoose representation:\n";
    std::cout << "  1. Adjacency Matrix\n";
    std::cout << "  2. Adjacency List\n";
    std::cout << ">> ";
    int choice;
    std::cin >> choice;
    if (choice == 1) return RepType::MATRIX;
    return RepType::LIST;
}

static void printResults(const ShortestPathResult& result, int source, int V) {
    if (result.hasNegativeCycle) {
        std::cout << "\n[!] Negative-weight cycle detected! Path results may be invalid.\n";
    }

    std::cout << "\nShortest paths from vertex " << source << ":\n";
    printSeparator();
    std::cout << "Dest\tDist\tPath\n";
    printSeparator();

    for (int v = 0; v < V; ++v) {
        std::cout << v << "\t";

        if (result.dist[v] == INT_MAX) {
            std::cout << "INF\t(unreachable)\n";
        } else {
            std::cout << result.dist[v] << "\t";
            auto path = result.getPath(v);
            for (size_t i = 0; i < path.size(); ++i) {
                if (i > 0) std::cout << " -> ";
                std::cout << path[i];
            }
            std::cout << "\n";
        }
    }
    printSeparator();
}

// ─── Main Menu ──────────────────────────────────────────────

int main() {
    std::unique_ptr<Graph> currentGraph;
    int startVertex = 0;
    RepType currentRep = RepType::LIST;

    while (true) {
        std::cout << "\n╔══════════════════════════════════════╗\n";
        std::cout << "║     SHORTEST PATH SOLVER             ║\n";
        std::cout << "╠══════════════════════════════════════╣\n";
        std::cout << "║  1. Load graph from file             ║\n";
        std::cout << "║  2. Generate random graph            ║\n";
        std::cout << "║  3. Display current graph            ║\n";
        std::cout << "║  4. Run Dijkstra                     ║\n";
        std::cout << "║  5. Run Bellman-Ford                 ║\n";
        std::cout << "║  6. Run benchmarks                   ║\n";
        std::cout << "║  7. Exit                             ║\n";
        std::cout << "╚══════════════════════════════════════╝\n";
        std::cout << ">> ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {

        // ── 1. Load graph from file ──
        case 1: {
            std::cout << "Enter file path: ";
            std::string filename;
            std::cin >> filename;
            currentRep = chooseRepresentation();

            try {
                currentGraph = readGraphFromFile(filename, currentRep, startVertex);
                std::cout << "\nGraph loaded: "
                          << currentGraph->getVertexCount() << " vertices, "
                          << currentGraph->getEdgeCount() << " edges.\n";
                std::cout << "Start vertex: " << startVertex << "\n";
                std::cout << "Representation: "
                          << (currentRep == RepType::MATRIX ? "Matrix" : "List") << "\n";
            } catch (const std::exception& e) {
                std::cerr << "Error loading graph: " << e.what() << "\n";
            }
            break;
        }

        // ── 2. Generate random graph ──
        case 2: {
            int V;
            double density;
            std::cout << "Number of vertices: ";
            std::cin >> V;
            std::cout << "Density (0.0 - 1.0): ";
            std::cin >> density;
            currentRep = chooseRepresentation();

            currentGraph = generateRandomGraph(V, density, currentRep, false);
            startVertex = 0;

            std::cout << "\nRandom graph generated: "
                      << currentGraph->getVertexCount() << " vertices, "
                      << currentGraph->getEdgeCount() << " edges.\n";
            std::cout << "Start vertex: " << startVertex << "\n";
            break;
        }

        // ── 3. Display current graph ──
        case 3: {
            if (!currentGraph) {
                std::cout << "No graph loaded. Use option 1 or 2 first.\n";
                break;
            }
            std::cout << "\nGraph (" 
                      << (currentRep == RepType::MATRIX ? "Matrix" : "List")
                      << " representation):\n";
            printSeparator();
            printGraph(*currentGraph);
            std::cout << startVertex << "\n";
            printSeparator();
            break;
        }

        // ── 4. Run Dijkstra ──
        case 4: {
            if (!currentGraph) {
                std::cout << "No graph loaded. Use option 1 or 2 first.\n";
                break;
            }
            std::cout << "\nRunning Dijkstra from vertex " << startVertex << "...\n";
            auto result = dijkstra(*currentGraph, startVertex);
            printResults(result, startVertex, currentGraph->getVertexCount());
            break;
        }

        // ── 5. Run Bellman-Ford ──
        case 5: {
            if (!currentGraph) {
                std::cout << "No graph loaded. Use option 1 or 2 first.\n";
                break;
            }
            std::cout << "\nRunning Bellman-Ford from vertex " << startVertex << "...\n";
            auto result = bellmanFord(*currentGraph, startVertex);
            printResults(result, startVertex, currentGraph->getVertexCount());
            break;
        }

        // ── 6. Run benchmarks ──
        case 6: {
            // Ensure results directory exists
            std::filesystem::create_directories("results");
            std::string csvPath = "results/benchmark_results.csv";
            std::cout << "\nStarting benchmark suite...\n";
            std::cout << "This may take several minutes for large vertex counts.\n";
            runBenchmarks(csvPath);
            break;
        }

        // ── 7. Exit ──
        case 7: {
            std::cout << "Goodbye!\n";
            return 0;
        }

        default:
            std::cout << "Invalid choice. Please enter 1-7.\n";
            break;
        }
    }

    return 0;
}
