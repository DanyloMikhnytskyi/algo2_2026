#pragma once

#include "Graph.h"
#include "ShortestPathResult.h"

// Dijkstra's algorithm using a min-heap (priority queue).
// Assumes all edge weights are non-negative.
// Returns shortest distances and predecessor array from source to all vertices.
ShortestPathResult dijkstra(const Graph& g, int source);
