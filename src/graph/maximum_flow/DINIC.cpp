// Description: グラフに対する最大流
// TimeComplexity: $ \mathcal{O}(EV^2) $ but fast
// Verifyed: AOJ GRL_6_A

W dinic(G &graph, int s, int t) {
	const W inf = 1LL << 50;
	const int n = graph.size();
	vector<int> level(n), iter(n);

	auto bfs = [&](int s, int t) {
		fill(begin(level), end(level), -1);
		queue<int> q;
		level[s] = 0, q.push(s);

		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (auto &e : graph[v]) {
				if (level[e.to] == - 1 and e.cap > e.flow) {
					level[e.to] = level[v] + 1;
					q.push(e.to);
				}
			}
		}
		return (level[t] !=  -1);
	};

	auto dfs = [&](int v, int t, W f) {
		auto func = [&](int v, int t, W f, auto func)->W{

			if (v == t) return f;
			for (int &i = iter[v]; i < graph[v].size(); i++) {
				edge &e = graph[v][i];

				if (e.cap > e.flow and level[v] < level[e.to]) {

					W d = func(e.to, t, min(f, e.cap - e.flow), func);

					if (d > 0) {
						e.flow += d, graph[e.to][e.rev].flow -= d;
						return d;
					}
				}
			}

			return 0;
		};
		return func(v, t, f, func);
	};

	while (bfs(s, t)) {
		fill(begin(iter), end(iter), 0);
		while (dfs(s, t, inf) != 0 );
	}

	W ret = 0;
	for (auto &e : graph[s]) ret += e.flow;
	return ret;
}