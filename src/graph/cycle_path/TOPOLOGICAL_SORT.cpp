// Description: 有向グラフに対するトポロジカルソート
// TimeComplexity: $ \mathcal{O}(V + E) $
// Verifyed: AOJ GRL_4_B

auto topological_sort(const G& graph) {
	const int n = graph.size();
	vector<int> used(n, 0), order;

	auto dfs = [&](int v) {
		auto func = [&](int v, auto func)->void{
			used[v] = true;
			for (auto &e : graph[v]) if (!used[e.to]) func(e.to, func);
			order.push_back(v);
		};
		return func(v, func);
	};

	rep(v, n)if (!used[v]) dfs(v);
	reverse(_all(order));
	return order;
}