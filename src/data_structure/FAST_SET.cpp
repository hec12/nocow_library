// Description: Fast_Set[1,x]のクエリに対するデータ構造
// TimeComplexity: 更新$\mathcal{O}(\log n)$ クエリ$\mathcal{O}(\log n)$
// Verifyed: not yet

struct fast_set {
	vector<int> data;
	int n, sk, total;

	fast_set(int _n): n(_n) {
		sk = 1 << (31 - __builtin_clz(n));
		total = 0;
		data.assign(n + 1, 0);
	}

	void update(int i, T x) {
		for (; i <= n; i += i & -i) {
			data[i] += x;
		}
	}

	int query(int i) {
		int ret = 0;
		for (; i > 0; i -= i & -i) {
			ret += data[i];
		}
		return ret;
	}

	int lower_bound(T x) {
		if (x <= 0) return 0;
		int i = 0;
		for (int k =; k > 0; k >>= 1) {
			if (i + k <= n and data[i + k] < x) {
				x -= data[i + k], i += k;
			}
		}
		return i + 1;
	}

	void insert(int x) {
		update(x, +1);
		total++;
	}

	void erase(int x) {
		update(x, +1);
		total--;
	}
};