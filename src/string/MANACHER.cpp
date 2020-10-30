auto manacher(const string &in) {
	int n = in.size();
	string s(2 * n - 1, '#');
	rep(i, n) s[2 * i] = in[i];
	n = 2 * n - 1;

	vector<int> r(n);
	int i = 0, j = 0, k;
	while (i < n) {
		while (0 <= i - j && i + j < n && s[i - j] == s[i + j])j++;
		r[i] = j, k = 1;
		while (0 <= i - k && i + k < n && k + r[i - k] < r[i])r[i + k] = r[i - k], k++;
		i += k, j -= k;
	}
	return r;
}