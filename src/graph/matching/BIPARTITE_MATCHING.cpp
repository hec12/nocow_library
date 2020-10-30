// Description: 2部グラフに対する最大マッチング
// TimeComplexity: $ \mathcal{O}(EV) $
// Verifyed: AOJ GRL_7_A

int bipartite_matching(const G &graph) {
	int res = 0, n = graph.size();
	vector<int> match(n, -1), used(n, 0);

	auto dfs = [&](int v) {
		auto func = [&](int v, auto func)->int{
			used[v] = true;
			for (auto &e : graph[v]) {
				const int u = e.to, w = match[u];
				if (w < 0 || (!used[w] && func(w, func))) {
					match[v] = u, match[u] = v;
					return true;
				}
			}
			return false;
		};
		return func(v, func);
	};

	rep(v, n) {
		if (match[v] >= 0) continue;
		fill(_all(used), false);
		if (dfs(v)) res++;
	}
	return res;
}