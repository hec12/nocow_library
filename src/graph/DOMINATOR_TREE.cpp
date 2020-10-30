// Description: Dominator Tree
// TimeComplexity: $\mathcal{O}(M \log N)$
// Verifyed: AOJ 0294

struct Union_find {
	Union_find(int n) {
		par.resize(n), iota(_all(par), 0);
		idx.resize(n), iota(_all(idx), 0);
		semi.assign(n, -1);
	}

	int find(int x) {
		if (par[x] == x) return x;
		int r = find(par[x]);
		if (semi[idx[par[x]]] < semi[idx[x]]) idx[x] = idx[par[x]];
		return par[x] = r;
	}

	void link(int a, int b) {par[b] = a;}
	int eval(int x) {find(x); return idx[x];}

	vector<int> par, idx, semi;
};

auto dominator_tree(G &graph, int root) {
	const int n = graph.size();

	G rgraph(n);
	rep(v, n) for (auto &e : graph[v]) add_edge(rgraph, e.to, v, e.cost);

	Union_find uf(n);

	vector<int> id(n, -1), par(n), u(n, -1);
	int total = 0;

	auto dfs = [&](int v, int p) {
		auto func = [&](int v, int p, auto func)->void{
			uf.semi[v] = total, id[total++] = v, par[v] = p;
			for (auto &e : graph[v]) {
				if (uf.semi[e.to] >= 0) continue;
				func(e.to, v, func);
			}
		};
		return func(v, p, func);
	};

	dfs(root, -1);
	vector<vector<int>> bucket(n);

	rrep(i, n, 1) {
		int v = id[i];
		for (auto &e : rgraph[v]) {
			int u = uf.eval(e.to);
			chmin(uf.semi[v], uf.semi[u]);
		}

		bucket[id[uf.semi[v]]].push_back(v);

		for (auto &nv : bucket[par[v]]) u[nv] = uf.eval(nv);
		bucket[par[v]].clear();
		uf.link(par[v], v);
	}

	vector<int> idom(n, 0);

	rep(i, 1, n) {
		int v = id[i], w = u[v];
		idom[v] = (uf.semi[v] == uf.semi[w]) ? uf.semi[v] : idom[w];
	}

	rep(i, 1, n) {
		int v = id[i];
		idom[v] = id[idom[v]];
	}

	idom[root] = -1;
	return idom;
}
