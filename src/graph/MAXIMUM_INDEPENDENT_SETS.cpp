// Description: 無向グラフに対する最大独立集合
// TimeComplexity: $ \mathcal{O}(1.466^VV) $
// Verified: not

auto maximum_independent_sets(const G& graph) {
	const int n = graph.size();
	using T = bitset<40>;
	vector<T> edge(n);
	rep(i, n) for (auto &e : graph[i]) edge[i].set(e.to);

	auto dfs = [&](int v, T used) {
		auto func = [&](int v, T used, auto func)->T{
			if (v == n) return T("0");
			if (used[v]) return func(v + 1, used, func);

			used.set(v);
			T ret = func(v + 1, used | edge[v], func);
			ret.set(v);

			if (((~used)&edge[v]).count() >= 2) {
				T arg = func(v + 1, used, func); // not used v
				if (ret.count() <= arg.count()) ret = arg;
			}

			return ret;
		};
		return func(v, used, func);
	};
	return dfs(0, T());
}
