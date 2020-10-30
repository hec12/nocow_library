// Verified: AOJ 2450
template <int V> struct HLD {
	int par[V], depth[V], heavy[V];
	int head[V], vid[V], inv[V];

	int dfs(const G& graph, int v, int p) {
		int sz = 1, smax = 0;
		for (auto &e : graph[v]) {
			if (e.to == p) continue;
			par[e.to] = v, depth[e.to] = depth[v] + 1;

			int sub_sz = dfs(graph, e.to, v);
			sz += sub_sz;

			if (smax < sub_sz) {
				smax = sub_sz, heavy[v] = e.to;
			}
		}
		return sz;
	}

	void init(const G& graph) {
		const int n = graph.size();
		fill_n(heavy, n, -1);
		dfs(graph, 0, -1);

		int id = 0;
		queue<int> q({ 0 });
		while (!q.empty()) {
			int h = q.front(); q.pop();
			for (int v = h; v != -1; v = heavy[v]) {
				inv[id] = v, vid[v] = id++, head[v] = h;
				for (auto &e : graph[v]) {
					if (e.to == par[v] or e.to == heavy[v]) continue;
					q.push(e.to);
				}
			}
		}
	}

	// 頂点属性の for_each （有向 fの3番目の引数には順方向なら0、逆方向なら1が渡される
	void for_each_v_directed(int u, int v, auto &f) {
		if (vid[u] > vid[v]) {
			f(max(vid[head[u]], vid[v]), vid[u] + 1, 1);
			if (head[u] != head[v]) for_each_v_directed(parent[head[u]], v, f);
		} else {
			f(max(vid[head[v]], vid[u]), vid[v] + 1, 0);
			if (head[u] != head[v]) for_each_v_directed(u, parent[head[v]], f);
		}
	}

	// 辺属性の for_each （有向 fの3番目の引数には順方向なら0、逆方向なら1が渡される
	void for_each_e_directed(int u, int v, auto &f) {
		if (vid[u] > vid[v]) {
			if (head[u] != head[v]) {
				f(vid[head[u]], vid[u], 1);
				for_each_e(par[head[u]], v, f);
			} else {
				if (u != v) f(vid[v] + 1, vid[u], 1);
			}
		} else {
			if (head[u] != head[v]) {
				f(vid[head[v]], vid[v], 0);
				for_each_e_directed(u, par[head[v]], f);
			} else {
				if (u != v) f(vid[u] + 1, vid[v], 0);
			}
		}
	}

	// 頂点 u の d 個上の頂点を求める（存在しないなら0を返す）
	int ancestor(int u, int d) {
		while (1) {
			if (depth[head[u]] <= depth[u] - d) break;
			d -= depth[u] - depth[head[u]] + 1;
			if (head[u] == 0) return 0;
			u = parent[head[u]];
		}
		return inv[vid[u] - d];
	}

	// 頂点 u と頂点 v の LCA を求める
	int lca(int u, int v) {
		if (vid[u] > vid[v]) swap(u, v);
		if (head[u] == head[v]) return u;
		return lca(u, parent[head[v]]);
	}

	// 頂点 u と頂点 v の距離を求める
	int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)];}
};

HLD<nmax> hld;

int main(void{
	hld.init(tree);
	auto func = [&](int u, int v, int d) {
		seg.range_update(u, v);
	};
	hld.for_each_vertex_directed(a, b, func);
	return 0;
}