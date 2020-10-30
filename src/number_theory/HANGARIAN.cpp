vector<int> min_cost_match(vector<vector<int>> a) {
	int n = a.size(), m = a[0].size();
	vector<int> left(n, -1), right(m, -1);
	vector<int> ofsleft(n, 0), ofsright(m, 0);
	auto cost = [&](int i, int j) { return a[i][j] + ofsleft[i] + ofsright[j];};

	rep(r, n) {
		vector<bool> s(n, false), t(m, false);
		vector<int> trace(m, -1), edge(m, r);
		s[r] = true;

		int b = -1;
		while (1) {
			int d = numeric_limits<int>::max();
			rep(j, m) if (!t[j]) d = min(d, cost(edge[j], j));
			rep(i, n) if (s[i]) ofsleft[i] -= d;
			rep(j, m) if (t[j]) ofsright[j] += d;

			rep(j, m) if (!t[j] && cost(edge[j], j) == 0) b = j;
			trace[b] = edge[b];
			int c = right[b];
			if (c < 0) break;

			s[c] = t[b] = true;
			rep(j, m) if (cost(c, j) < cost(edge[j], j)) edge[j] = c;
		}
		while (b >= 0) {
			int a = trace[b], nb = left[a];
			right[b] = a, left[a] = b, b = nb;
		}
	}
	return left;
}
