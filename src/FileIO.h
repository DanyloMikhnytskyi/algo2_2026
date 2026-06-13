#pragma once

#include "Graph.h"
#include <string>
#include <memory>

// Read a directed graph from a text file.
// Format:
//   Line 1: V E
//   Next E lines: u v w
//   Last line: startVertex
// Returns the graph and sets startVertex by reference.
std::unique_ptr<Graph> readGraphFromFile(const std::string& filename,
                                          RepType rep,
                                          int& startVertex);

// Print the graph to stdout in the same file format (without start vertex line).
void printGraph(const Graph& g);
