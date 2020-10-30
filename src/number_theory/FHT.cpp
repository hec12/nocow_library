void fht(vector<int> &a, int l, int r) {
	if (r - l == 1) return;
	const int half = (r - l) / 2;
	const int m = (l + r) / 2;

	fht(a, l, m), fht(a, m, r);
	for (int i = l; i < m; i++) {
		int b[2] = {a[i], a[i + half]};
		a[i] = (b[0] + b[1]) % mod;
		a[i + half] = (b[0] + mod -  b[1]) % mod;
	}
}
