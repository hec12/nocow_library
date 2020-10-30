// Description: 文字列のパターンマッチングオートマトン
// TimeComplexity: $\mathcal{O}(|S|)$
// Verifyed: CF 201 B Todo

// kmp[i]=s[0,i-1]のprefixとsuffixの最長共通文字列の長さ
auto init(const string &s) {
	int n = s.size(), j = -1;
	vector<int> kmp(n + 1, -1);

	rep(i, n) {
		while (j >= 0 && s[i] != s[j]) j = kmp[j];
		j++, kmp[i + 1] = (s[i] == s[j]) ? kmp[j] : j;
	}
	return kmp;
}

int match(string p, string s, const auto &kmp) {
	int cur = 0, m = p.size(), n = s.size();
	rep(i, n) {
		while (cur >= 0 && s[i] != p[cur]) cur = kmp[cur];
		cur++;
		if (cur >= m) return cur; // cur=kmp[cur];
	}
	return cur;
}