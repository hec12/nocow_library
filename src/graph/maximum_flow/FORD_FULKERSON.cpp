using edge = struct {int to, cap, rev;};
using G = vector<vector<edge>>;
const int inf = 1 << 29;

void add_edge(G &graph, int a, int b, int c) {
	graph[a].push_back({b, c, int(graph[b].size())});
	graph[b].push_back({a, 0, int(graph[a].size() - 1)});
}

int max_flow(G &graph, int s, int t) {
	int n = graph.size(), flow = 0;
	vector<int> used(n);

	auto dfs = [&](int v, int t, int f, const auto & self)->int{
		if (v == t) return f;
		used[v] = true;
		for (auto &e : graph[v]) {
			if (used[e.to] || e.cap <= 0) continue;
			int d = self(e.to, t, min(f, e.cap), self);
			if (d > 0) {
				e.cap -= d;
				graph[e.to][e.rev].cap += d;
				return d;
			}
		}
		return 0;
	};

	while (1) {
		fill(_all(used), false);
		int f = dfs(s, t, inf, dfs);
		if (f == 0) break;
		flow += f;
	}
	return flow;
}