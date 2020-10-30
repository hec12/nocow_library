// Description: 連結グラフに対する最小シュタイナー木
// TimeComplexity: $ \mathcal{O}(V^3+ V^2 2^T + V3^T)$ Tはターミナル数
// Verifyed: AOJ 1040

auto Dreyfus_wagner(const G &graph, const auto &term) {
	using W = int; W inf = 1 << 28;
	const int n = int(graph.size()), t = int(term.size());
	if (t <= 1) return 0;
	auto dist = graph;
	vector<vector<W>> opt(1 << t, vector<W>(n, inf));

	rep(k, n)rep(i, n)rep(j, n) chmin(dist[i][j], dist[i][k] + dist[k][j]);

	map<int, int> dict;
	rep(i, t) {
		dict[term[i]] = 1 << i;
		rep(j, n) opt[1 << i][j] = dist[term[i]][j];
		rep(j, t) opt[(1 << i) | (1 << j)][term[j]] = dist[term[i]][term[j]];
	}

	auto next_combination = [&](int s) {
		int x = s & -s, y = s + x;
		return ((s & ~y) / x >> 1) | y;
	};

	rep(k, 2, t) {
		for (int s = (1 << k) - 1; s < (1 << t); s = next_combination(s)) {
			rep(i, n) {
				int ns = s | dict[i];
				if (dict[i] and s == ns) continue;
				for (int u = (s - 1)&s; u != 0; u = (u - 1)&s) {
					int c = s & (~u);
					chmin(opt[ns][i], opt[u][i] + opt[c][i]);
				}
			}
		}
		for (int s = (1 << k) - 1; s < (1 << t); s = next_combination(s)) {
			rep(i, n) {
				int ns = s | dict[i];
				if (dict[i] and s == ns) continue;
				rep(j, n) chmin(opt[ns][i], opt[s][j] + dist[j][i]);
			}
		}
	}

	const int mask = (1 << t) - 1;
	W ans = opt[mask][0];
	rep(i, n) chmin(ans, opt[mask][i]);
	return ans;
}