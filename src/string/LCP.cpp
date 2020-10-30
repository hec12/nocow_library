// Description: 文字列の最長共通接頭辞
// TimeComplexity: $\mathcal{O}(|S|)$
// Verifyed: ARC050 D

auto longest_common_prefix(string s, const auto &rnk, const auto &sa) {
	int n = s.size(), h = 0;
	vector<int> lcp(n + 1, 0);
	rep(i, n) {
		int j = sa[rnk[i] - 1];
		for (h = max(h - 1, 0); j + h < n && i + h < n; h++) if (s[j + h] != s[i + h]) break;
		lcp[rnk[i] - 1] = h;
	}
	return lcp;
}