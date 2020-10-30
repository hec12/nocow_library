// Description: 非負コストのグラフに対する単一始点最短経路
// TimeComplexity: $\mathcal{O}(E\log V)$
// Verifyed: AOJ GRL_1_A

auto dijkstra(const G &graph, int s) {
    const W inf = 1LL << 60;
    const int n = graph.size();

    vector<W> dist(n, inf);
    using state = tuple<W, int>;

    priority_queue<state, vector<state>, greater<state>> q;
    dist[s] = 0, q.push(state(0, s));

    while (!q.empty()) {
        W c; int v;
        tie(c, v) = q.top(); q.pop();
        for (auto &e : graph[v]) {
            W nc = c + e.cost; int nv = e.to;
            if (chmin(dist[nv], nc)) q.push(state(nc, nv));
        }
    }
    return dist;
}