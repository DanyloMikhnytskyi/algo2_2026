#pragma once

#include <string>

// Run the full benchmark suite:
//   - Vertex counts: {10, 50, 100, 500, 1000}
//   - Densities: {25%, 50%, 75%, 100%}
//   - Representations: {Matrix, List}
//   - Algorithms: {Dijkstra, Bellman-Ford}
//   - 100 random graph instances per combination
// Results are written to a CSV file.
void runBenchmarks(const std::string& outputCsvPath);
