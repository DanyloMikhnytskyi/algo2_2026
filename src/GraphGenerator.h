#pragma once

#include "Graph.h"
#include <memory>

// Generate a random directed graph with the given vertex count and edge density.
// density: fraction of max possible edges [0.0, 1.0]
//   max edges for directed graph without self-loops = V * (V - 1)
// allowNegative: if true, weights range in [-50, 100]; otherwise [1, 100]
std::unique_ptr<Graph> generateRandomGraph(int V,
                                            double density,
                                            RepType rep,
                                            bool allowNegative = false);
