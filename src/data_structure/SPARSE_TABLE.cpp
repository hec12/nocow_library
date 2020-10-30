template <int depth> struct Sparse_table {
	using T = int;
	const static int h = depth;
	const static int n = 1 << h;
	T data[h + 1][n];

	inline T vmerge(T a, T b) {return max(a, b);}

	void init(const vector<T> &a) {
		const int m = a.size();
		rep(i, m) data[0][i] = a[i];

		rep(k, h) {
			const int offset = 1 << k;
			rep(i, m - 2 * offset + 1) {
				data[k + 1][i] = vmerge(data[k][i], data[k][i + offset]);
			}
		}
	}

	T query(int l, int r) {
		const int offset = 1 << (31 - __builtin_clz(r - l));
		return vmerge(data[i][l], data[i][r - offset]);
	}
};
