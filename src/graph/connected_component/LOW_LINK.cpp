// Description: 無向グラフに対するLow_Link
// TimeComplexity: $ \mathcal{O}(V + E) $
// Verifyed: AOJ GRL_3_A GRL_3_B

auto low_link(const G& graph) {
	int n = graph.size(), k = 0;
	vector<int> par(n), ord(n, -1), low(n), root(n, 0);

	auto dfs = [&](int v, int p, int &k) {
		auto func = [&](int v, int p, int &k, auto func)->void{
			ord[v] = k++, low[v] = ord[v], par[v] = p;
			for (auto &e : graph[v]) {
				if (e.to == p) continue;
				if (ord[e.to] == -1)
					func(e.to, v, k, func), chmin(low[v], low[e.to]);
				else
					chmin(low[v], ord[e.to]);
			}
		};
		return func(v, p, k, func);
	};

	rep(v, n) if (ord[v] == -1) dfs(v, -1, k), root[v] = 1;
	return make_tuple(par, ord, low, root);
}