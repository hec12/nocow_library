// Description: セグメント木　点更新 区間クエリ
// TimeComplexity: 初期化$\mathcal{O}(n \log n)$ 更新とクエリ$\mathcal{O}(\log n)$
// Verifyed: AOJ DSL_2_A

template <int depth> struct Segment_tree {
	const static int h = depth;
	const static int n = 1 << h;

	using T = long long;
	T data[2 * n];
	const T out = (1LL << 31) - 1;

	inline T vmerge(T l, T r) {return min(l, r);}

	void init() {
		fill_n(data, 2 * n, out);
	}

	void update(int p, T x) { // set value at position p
		for (data[p += n] = x; p > 1; p >>= 1){
			data[p >> 1] = vmerge(data[p], data[p ^ 1]);
		}
	}

	T query(int l, int r) {  // sum on interval [l, r)
		T resl = out, resr = out;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) resl = vmerge(data[l++], resl);
			if (r & 1) resr = vmerge(resr, data[--r]);
		}
		return vmerge(resl, resr);
	}
};
