// Description: 連結グラフに対する最小無向全域木
// TimeComplexity: $ \mathcal{O}(E \log V) $
// Verifyed: AOJ GRL_2_A
// Required: Union-Find

auto kruskal(const G &graph) {
	using W = ll;
	const int n = graph.size();
	using state = tuple<W, int, int>; //(cost,from,to)
	priority_queue<state, vector<state>, greater<state>> q;
	rep(v, n)for (auto &e : graph[v]) q.push(state(e.cost, v, e.to));
	Union_find uf(n);

	W res = 0;
	while (!q.empty()) {
		int a, b; W c;
		tie(c, a, b) = q.top(); q.pop();
		if (!uf.same(a, b)) uf.unite(a, b), res += c;
	}
	return res;
}