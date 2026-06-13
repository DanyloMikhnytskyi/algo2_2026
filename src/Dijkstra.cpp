#include "Dijkstra.h"
#include <queue>
#include <climits>

ShortestPathResult dijkstra(const Graph& g, int source) {
    int V = g.getVertexCount();
    ShortestPathResult result;
    result.dist.assign(V, INT_MAX);
    result.prev.assign(V, -1);

    // Min-heap: (distance, vertex)
    using PQEntry = std::pair<int, int>;
    std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<PQEntry>> pq;

    result.dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // Skip stale entries (lazy deletion)
        if (d > result.dist[u]) {
            continue;
        }

        for (const auto& [v, w] : g.getNeighbors(u)) {
            int newDist = result.dist[u] + w;
            if (newDist < result.dist[v]) {
                result.dist[v] = newDist;
                result.prev[v] = u;
                pq.push({newDist, v});
            }
        }
    }

    return result;
}
