#pragma once

#include "Graph.h"
#include "ShortestPathResult.h"

// Bellman-Ford algorithm.
// Handles negative edge weights and detects negative-weight cycles.
// Returns shortest distances, predecessor array, and negative-cycle flag.
ShortestPathResult bellmanFord(const Graph& g, int source);
