#pragma once

#include <vector>
#include <algorithm>
#include <climits>

// Holds the result of a shortest-path algorithm run
struct ShortestPathResult {
    std::vector<int> dist;   // dist[v] = shortest distance from source to v
    std::vector<int> prev;   // prev[v] = predecessor of v on shortest path
    bool hasNegativeCycle = false;

    // Reconstruct the path from source to dest
    // Returns empty vector if dest is unreachable
    std::vector<int> getPath(int dest) const {
        if (dest < 0 || dest >= static_cast<int>(dist.size())) return {};
        if (dist[dest] == INT_MAX) return {};

        std::vector<int> path;
        for (int v = dest; v != -1; v = prev[v]) {
            path.push_back(v);
            // Safety check: if path length exceeds vertex count, there's a cycle in prev
            if (static_cast<int>(path.size()) > static_cast<int>(dist.size())) {
                return {}; // corrupted path (shouldn't happen with valid input)
            }
        }
        std::reverse(path.begin(), path.end());
        return path;
    }
};
