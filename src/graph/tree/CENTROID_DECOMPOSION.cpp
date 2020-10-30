bool used[limit];
int sz[limit];
vector<int> centroid;

int serach_centroid(const G &graph, int v, int p, int total) {
	sz[v] = 1;
	const int thr = total / 2;
	bool ok = true;

	for (auto &v2 : graph[v]) {
		if (v2 == p or used[v2]) continue;
		sz[v] += dfs(graph,v2, v, total);
		if (sz[v2] > thr) ok = false;
	}

	if (total - sz[v] > thr) ok = false;
	if (ok) centroid.push_back(v);

	return sz[v];
}
