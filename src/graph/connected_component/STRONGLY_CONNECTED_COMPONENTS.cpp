// Description: 有向グラフに対する強連結成分
// TimeComplexity: $ \mathcal{O}(V + E) $
// Verifyed: AOJ GRL_3_C

auto strongly_connected_components(const G& graph) {
	int n = graph.size(), k = 0;
	vector<int> par(n), ord(n, -1), low(n), scc(n, -1), res;
	stack<int> s;

	auto dfs = [&](int v, int p, int &k) {
		auto func = [&](int v, int p, int &k, auto func)->void{
			ord[v] = k++, low[v] = ord[v], par[v] = p, s.push(v);
			for (auto &e : graph[v]) {
				if (scc[e.to] != -1) continue;
				if (ord[e.to] == -1)
					func(e.to, v, k, func), chmin(low[v], low[e.to]);
				else
					chmin(low[v], ord[e.to]);
			}
			if (ord[v] != low[v]) return ;
			while (1) {
				int u = s.top(); s.pop();
				scc[u] = v;
				if (u == v) break;
			}
		};
		return func(v, p, k, func);
	};

	rep(v, n) if (ord[v] == -1) dfs(v, -1, k);
	return scc;
}