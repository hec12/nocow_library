// Description: 無向グラフに対する橋
// TimeComplexity: $ \mathcal{O}(V + E) $
// Verifyed: AOJ GRL_3_B
// Required: Low-link

auto bridge(const G& graph) {
	const int n = graph.size();
	vector<int> par, ord, low, root;
	tie(par, ord, low, root) = low_link(graph);

	using state = tuple<int, int>;
	vector<state> res;
	rep(v, n) {
		if (par[v] == -1) continue;
		if (ord[v] < low[par[v]] || ord[par[v]] < low[v]) {
			auto in = state(v, par[v]);
			if (get<1>(in) <= get<0>(in)) swap(get<0>(in), get<1>(in));
			res.push_back(in);
		}
	}
	sort(_all(res));
	return res;
}