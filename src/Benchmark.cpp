#include "Benchmark.h"
#include "Graph.h"
#include "GraphGenerator.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <iomanip>
#include <functional>
#include <memory>

// Helper: measure execution time of a shortest-path algorithm in microseconds
static double measureAlgorithm(const Graph& graph,
                                int source,
                                const std::function<ShortestPathResult(const Graph&, int)>& algo) {
    auto start = std::chrono::high_resolution_clock::now();
    volatile auto result = algo(graph, source); // volatile to prevent optimization
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::micro>(end - start).count();
}

void runBenchmarks(const std::string& outputCsvPath) {
    // Configuration
    const std::vector<int> vertexCounts = {10, 50, 100, 500, 1000};
    const std::vector<double> densities = {0.25, 0.50, 0.75, 1.00};
    const std::vector<RepType> reps = {RepType::MATRIX, RepType::LIST};
    const int NUM_INSTANCES = 100;
    const int SOURCE_VERTEX = 0;

    struct AlgoInfo {
        std::string name;
        std::function<ShortestPathResult(const Graph&, int)> func;
    };

    std::vector<AlgoInfo> algorithms = {
        {"Dijkstra",    dijkstra},
        {"BellmanFord", bellmanFord}
    };

    // Open CSV file
    std::ofstream csv(outputCsvPath);
    if (!csv.is_open()) {
        std::cerr << "Error: cannot open output file: " << outputCsvPath << "\n";
        return;
    }
    csv << "algorithm,representation,vertices,density,avg_time_us\n";

    // Total number of combinations for progress display
    int totalCombinations = static_cast<int>(
        algorithms.size() * reps.size() * vertexCounts.size() * densities.size());
    int currentCombo = 0;

    std::cout << "\n========================================\n";
    std::cout << "  BENCHMARK SUITE\n";
    std::cout << "  " << NUM_INSTANCES << " instances per combination\n";
    std::cout << "  " << totalCombinations << " total combinations\n";
    std::cout << "========================================\n\n";

    for (const auto& algo : algorithms) {
        for (const auto& rep : reps) {
            std::string repName = (rep == RepType::MATRIX) ? "Matrix" : "List";

            for (int V : vertexCounts) {
                for (double density : densities) {
                    currentCombo++;
                    int densityPercent = static_cast<int>(density * 100);

                    std::cout << "[" << currentCombo << "/" << totalCombinations << "] "
                              << algo.name << " | " << repName
                              << " | V=" << V << " | D=" << densityPercent << "%"
                              << " ... " << std::flush;

                    double totalTime = 0.0;

                    for (int i = 0; i < NUM_INSTANCES; ++i) {
                        auto graph = generateRandomGraph(V, density, rep, false);
                        totalTime += measureAlgorithm(*graph, SOURCE_VERTEX, algo.func);
                    }

                    double avgTime = totalTime / NUM_INSTANCES;

                    std::cout << std::fixed << std::setprecision(2)
                              << avgTime << " us (avg)\n";

                    csv << algo.name << ","
                        << repName << ","
                        << V << ","
                        << densityPercent << ","
                        << std::fixed << std::setprecision(2) << avgTime << "\n";
                }
            }
        }
    }

    csv.close();
    std::cout << "\nBenchmark complete. Results saved to: " << outputCsvPath << "\n";
}
