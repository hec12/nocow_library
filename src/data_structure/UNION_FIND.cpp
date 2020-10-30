// Description: 素集合を管理するデータ構造
// TimeComplexity: 初期化$\mathcal{O}(n)$ 更新$\mathcal{O}(\log n)$
// Verifyed: AOJ DSL_1_A

struct Union_find {
	Union_find(int n) {data.assign(n, -1);}
	int find(int x) {return (data[x] < 0) ? x : data[x] = find(data[x]);}
	void unite(int a, int b) {
		a = find(a), b = find(b);
		if (a != b) {
			if (data[a] < data[b]) swap(a, b);
			data[a] += data[b], data[b] = a;
		}
	}
	bool same(int a, int b) {return find(a) == find(b);}
	int size(int x) {return -data[find(x)];}
	vector<int> data;
};
