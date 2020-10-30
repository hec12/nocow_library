void tree_height(int n) {
	function<void(int, int, ll)> dfs = [&dfs](int v, int p, ll c) {
		dist[v] = c;
		for (auto &e : graph[v]) if (e.to != p) dfs(e.to, v, c + e.cost);
	};
	dfs(0, -1, 0LL);
	int u = 0; rep(i, n) if (dist[i] > dist[u]) u = i;
	dfs(u, -1, 0LL);
	int v = 0; rep(i, n) if (dist[i] > dist[v]) v = i;
	function<void(int, int, ll, int)> dfs2 = [&dfs2](int v, int p, ll c, int s) {
		cmax[v] = max(cmax[v], c);
		for (auto &e : graph[v]) if (e.to != p) dfs2(e.to, v, c + e.cost, s);
	};
	dfs2(u, -1, 0LL, u);
	dfs2(v, -1, 0LL, v);
}