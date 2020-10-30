// Description: 文字列の接尾辞配列
// TimeComplexity: $\mathcal{O}(|S|\log^2|S|)$
// Verifyed: ARC050 D

auto suffix_array(string s) {
	const int n = s.size();
	vector<int> sa(n + 1), rnk(n + 1, 0), tmp(n + 1, 0);
	rep(i, n + 1) sa[i] = i, rnk[i] = (i < n ? s[i] : -1);
	for (int k = 1; k <= n; k <<= 1) {
		auto cmp = [&](int i, int j) {
			if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
			int ci = (i + k <= n) ? rnk[i + k] : -1;
			int cj = (j + k <= n) ? rnk[j + k] : -1;
			return ci < cj;
		};
		sort(begin(sa), end(sa), cmp);
		tmp[sa[0]] = 0;
		rep(i, n) tmp[sa[i + 1]] = tmp[sa[i]] + cmp(sa[i], sa[i + 1]);
		rep(i, n + 1) rnk[i] = tmp[i];
	}
	return make_tuple(rnk, sa);
}