#include "BellmanFord.h"
#include <climits>

ShortestPathResult bellmanFord(const Graph& g, int source) {
    int V = g.getVertexCount();
    ShortestPathResult result;
    result.dist.assign(V, INT_MAX);
    result.prev.assign(V, -1);
    result.dist[source] = 0;

    // Collect all edges once
    std::vector<Edge> edges = g.getAllEdges();

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; ++i) {
        bool updated = false;
        for (const auto& e : edges) {
            if (result.dist[e.from] != INT_MAX &&
                result.dist[e.from] + e.weight < result.dist[e.to]) {
                result.dist[e.to] = result.dist[e.from] + e.weight;
                result.prev[e.to] = e.from;
                updated = true;
            }
        }
        // Early exit if no updates in this pass
        if (!updated) break;
    }

    // Check for negative-weight cycles (one more pass)
    for (const auto& e : edges) {
        if (result.dist[e.from] != INT_MAX &&
            result.dist[e.from] + e.weight < result.dist[e.to]) {
            result.hasNegativeCycle = true;
            break;
        }
    }

    return result;
}
