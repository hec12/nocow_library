// Description: [1,x]のクエリに対するデータ構造
// TimeComplexity: 更新$\mathcal{O}(\log n)$ クエリ$\mathcal{O}(\log n)$
// Verifyed: ARC 033 C

template <int depth> struct Binary_indexed_tree {
	using T = int;

	const static int h = depth;
	const static int n = 1 << h;
	T data[n];

	void init() {
		fill_n(data, n, 0);
	}

	void update(int i, T x) {
		for (; i < n; i += i & -i) {
			data[i] += x;
		}
	}

	T query(int i) {
		T ret = 0;
		for (; i > 0; i -= i & -i) ret += data[i];
		return ret;
	}

	int lower_bound(T x) {
		if (x <= 0) return 0;
		int i = 0;
		for (int k = n; k > 0; k >>= 1) {
			if (i + k < n and data[i + k] < x)
				x -= data[i + k], i += k;
		}
		return i + 1;
	}
};
