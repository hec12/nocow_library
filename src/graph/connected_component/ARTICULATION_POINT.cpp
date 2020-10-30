// Description: 無向グラフに対する関節点
// TimeComplexity: $ \mathcal{O}(V + E) $
// Verifyed: AOJ GRL_3_A
// Required: Low-link

auto articulation_point(const G& graph) {
	const int n = graph.size();
	vector<int> par, ord, low, root;
	tie(par, ord, low, root) = low_link(graph);

	vector<int> res;
	rep(v, n) {
		if (root[v]) {
			int degree = 0;
			for (auto &e : graph[v]) if (v == par[e.to]) degree++;
			if (degree >= 2) res.push_back(v);
		} else {
			for (auto &e : graph[v]) {
				if (v == par[e.to] && ord[v] <= low[e.to]) {
					res.push_back(v);
					break;
				}
			}
		}
	}
	return res;
}