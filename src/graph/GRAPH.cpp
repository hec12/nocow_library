// Description: グラフの型定義
// Verifyed: Many Diffrent Problem

//Appropriately Changed
using edge = struct {int to;};
using G = vector<vector<edge>>;

//Appropriately Changed
void add_edge(G &graph, int from, int to) {
	graph[from].push_back({to});
	graph[to].push_back({from});
}

//Appropriately Changed
using W = ll;
using edge = struct {int to; W cost;};
using G = vector<vector<edge>>;

//Appropriately Changed
void add_edge(G &graph, int from, int to, W cost) {
	graph[from].push_back({to, cost});
	graph[to].push_back({from, cost});
}

//Appropriately Changed
using W = ll;
using edge = struct {int to, rev; W cap, flow;};
using G = vector<vector<edge>>;

//Appropriately Changed
void add_edge(G &graph, int from, int to, W cap) {
	graph[from].push_back({to, int(graph[to].size()) , cap , 0});
	graph[to].push_back({from, int(graph[from].size()) - 1, 0 , 0});
}

//Appropriately Changed
using W = ll;
using edge = struct {int to, rev; W cap, flow, cost;};
using G = vector<vector<edge>>;

//Appropriately Changed
void add_edge(G &graph, int from, int to, W cap, W cost) {
	graph[from].push_back({to, int(graph[to].size()) , cap , 0 , cost});
	graph[to].push_back({from, int(graph[from].size()) - 1, 0 , 0, -cost});
}
