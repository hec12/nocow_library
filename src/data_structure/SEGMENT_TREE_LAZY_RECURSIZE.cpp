template <int depth>  struct Segment_tree {
	const static int h = depth;
	const static int n = 1 << h;

	using T = long long;
	T data[2 * n], lazy[2 * n];
	const T out = (1LL << 31) - 1;

	inline T vmerge(T l, T r) {return min(l, r);}

	void init() {
		fill_n(data, 2 * n, out);
		fill_n(lazy, 2 * n, out);
	}

	// lazy_evaluation
	void apply(T v, int p, int l, int r) {
		data[p] = v;
		lazy[p] = v;
	}

	void push(int p, int l, int r) {
		const int m = (l + r) / 2;
		if (lazy[p] == out) return;
		apply(lazy[p], 2 * p + 1, l, m);
		apply(lazy[p], 2 * p + 2, m, r);
		lazy[p] = out;
	}

	void range_update(int a, int b, T x, int k = 0, int l = 0, int r = n) {
		if (r <= a or b <= l) return;
		if (a <= l and r <= b) return apply(x, k, l, r);
		push(k, l, r);
		const int m = (l + r) / 2;
		range_update(a, b, x, k * 2 + 1, l, m);
		range_update(a, b, x, k * 2 + 2, m, r);
		data[k] = vmerge(data[k * 2 + 1], data[k * 2 + 2]);
	}

	T range_query(int a, int b, int k = 0, int l = 0, int r = n) {
		if (r <= a or b <= l) return out;
		if (a <= l and r <= b) return data[k];
		push(k, l, r);
		const int m = (l + r) / 2;
		T vl = range_query(a, b, k * 2 + 1, l, m);
		T vr = range_query(a, b, k * 2 + 2, m, r);
		return vmerge(vl, vr);
	}
};

Segment_tree<17> seg;
