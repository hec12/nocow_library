// Description: Z[i]=sとs[i..]の最長共通部分列の長さ
// TimeComplexity: $\mathcal{O}(N)$
// Verifyed: ARC 060 D

auto z_algorithm(const string &s) {
	int n = s.size(), i = 1, j = 0, k;
	vector<int> z(n, n);
	while (i < n) {
		while (i + j < n && s[i + j] == s[j]) j++;
		z[i] = j, k = !!j;
		while (i + k < n && k + z[k] < j) z[i + k] = z[k], k++;
		i += k + !j, j -= k;
	}
	return z;
}