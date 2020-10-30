// Description: グラフに対する最小費用流
// TimeComplexity: $ \mathcal{O}(FEV) $
// Verifyed: AOJ GRL_6_B

W primal_dual(G &graph, int s, int t, int f) {
	const W inf = 1LL << 50;
	W res = 0;
	while (f) {
		int n = graph.size(), update;
		vector<W> dist(n, inf);
		vector<int> pv(n, 0), pe(n, 0);
		dist[s] = 0;

		rep(loop, n) {
			update = false;
			rep(v, n)rep(i, graph[v].size()) {
				edge &e = graph[v][i];
				if (e.cap > e.flow and chmin(dist[e.to], dist[v] + e.cost)) {
					pv[e.to] = v, pe[e.to] = i;
					update = true;
				}
			}
			if (!update) break;
		}

		if (dist[t] == inf) return -1;

		W d = f;
		
		for (int v = t; v != s; v = pv[v]){
			chmin(d, graph[pv[v]][pe[v]].cap - graph[pv[v]][pe[v]].flow);
		}

		f -= d, res += d * dist[t];

		for (int v = t; v != s; v = pv[v]) {
			edge &e = graph[pv[v]][pe[v]];
			e.flow += d;
			graph[v][e.rev].flow -= d;
		}
	}
	return res;
}
