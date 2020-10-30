// Description: フローの復元
// TimeComplexity: $ \mathcal{O}(E) $
// Verifyed: not

auto positive_edges(G &graph) {
	vector<pair<int, int>> ret;
	const int n = graph.size();
	rep(v, n) for (auto &e : graph[v]) {
		if (e.cap - e.flow > 0) {
			ret.push_back(make_pair(v, e.to));
		}
	}
	return ret;
}
