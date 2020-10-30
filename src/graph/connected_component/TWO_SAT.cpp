// Description: 2-SAT
// Verifyed: Many Diffrent Problem
// Required: 有向グラフに対する強連結成分

using edge = struct {int to;};
using G = vector<vector<edge>>;
void add_edge(G &graph, int from, int to) {
	graph[from].push_back({to});
}

// x&1 == 1 True
// x&1 == 0 False
void closure_or(G &graph, int a, int b) {
	add_edge(graph, a ^ 1, b);
	add_edge(graph, b ^ 1, a);
}

auto strongly_connected_components(const G& graph) {
	const int n = graph.size();

	vector<int> used(n, 0), order, scc(n, 0);

	auto dfs = [&](int v) {
		auto func = [&](int v, auto func)->void{
			used[v] = true;
			for (auto &e : graph[v]) if (!used[e.to]) func(e.to, func);
			order.push_back(v);
		};
		return func(v, func);
	};

	rep(v, n) if (used[v] == false) dfs(v);

	G rgraph(n);
	rep(v, n) for (auto &e : graph[v]) add_edge(rgraph, e.to, v);
	int total = 0;

	auto rdfs = [&](int v) {
		auto func = [&](int v, auto func)->void{
			used[v] = true, scc[v] = total;
			for (auto &e : rgraph[v]) if (!used[e.to]) func(e.to, func);
		};
		return func(v, func);
	};

	used.assign(2 * n, false);
	reverse(begin(order), end(order));

	for (auto &v : order) if (used[v] == false) rdfs(v), total++;
	return scc;
}

vector<int> get_variable(G &graph) {
	const int n = graph.size() / 2;
	vector<int> ret(n, 0);

	vector<int> scc;
	scc = strongly_connected_components(graph);

	rep(i, n) {
		if (scc[2 * i] == scc[2 * i + 1])
			ret[0] = -1;
		else
			ret[i] = (scc[2 * i] < scc[2 * i + 1]);
	}
	return ret;
}
