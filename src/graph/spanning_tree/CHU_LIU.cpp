// Description: 連結グラフに対する最小有向全域木
// TimeComplexity: $ \mathcal{O}(EV) $
// Verifyed: AOJ GRL_2_B

G chu_liu(const G &graph, int root) {
	using W = int; const W inf = 1 << 28;
	const int n = graph.size();

	vector<int> cost(n, inf), pv(n, -1);
	rep(v, n) for (auto &e : graph[v]) {
		if (chmin(cost[e.to], e.cost)) pv[e.to] = v;
	}

	int led = -1, unuse = -1;
	vector<int> comp(n), used(n, -1);
	iota(begin(comp), end(comp), 0);

	rep(v, n) if (used[v] == -1 and pv[v] != -1 and v != root) {
		int cur = used[v] = v;
		for (cur = pv[cur]; cur != root and used[cur] == -1; cur = pv[cur]) {
			used[cur] = v;
		}
		if (used[cur] != v) continue;
		led = cur, comp[cur] = cur, v = n;
		for (int w = pv[cur]; w != cur; w = pv[w]) {
			comp[w] = cur;
		}
	}

	G ngraph(n), ret(n);
	using E = tuple<int, int, int>; map<E, E> dict;

	if (led == -1) {
		rep(v, n) {
			if (v != root and pv[v] != -1) {
				add_edge(ret, pv[v], v, cost[v]);
			}
		}
	} else {
		rep(v, n) for (auto &e : graph[v]) {
			int a = comp[v], b = comp[e.to];
			if (a == b) continue;
			int c = e.cost - (comp[e.to] == led) * cost[e.to];
			dict[E(a, b, c)] = E(v, e.to, e.cost);
			add_edge(ngraph, a, b, c);
		}

		G ntree = chu_liu(ngraph, comp[root]);

		rep(v, n) for (auto &e : ntree[v]) {
			int a, b, c;
			tie(a, b, c) = dict[E(v, e.to, e.cost)];
			if (comp[b] == led) unuse = b;
			add_edge(ret, a, b, c);
		}

		rep(v, n) {
			if (comp[v] == led and v != unuse) {
				add_edge(ret, pv[v], v, cost[v]);
			}
		}
	}
	return ret;
}
