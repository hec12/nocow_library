#include <bits/stdc++.h>

#define _overload(_1,_2,_3,name,...) name
#define _rep(i,n) _range(i,0,n)
#define _range(i,a,b) for(int i=int(a);i<int(b);++i)
#define rep(...) _overload(__VA_ARGS__,_range,_rep,)(__VA_ARGS__)

#define _rrep(i,n) _rrange(i,n,0)
#define _rrange(i,a,b) for(int i=int(a)-1;i>=int(b);--i)
#define rrep(...) _overload(__VA_ARGS__,_rrange,_rrep,)(__VA_ARGS__)

#define _all(arg) begin(arg),end(arg)
#define uniq(arg) sort(_all(arg)),(arg).erase(unique(_all(arg)),end(arg))
#define getidx(ary,key) lower_bound(_all(ary),key)-begin(ary)
#define clr(a,b) memset((a),(b),sizeof(a))
#define bit(n) (1LL<<(n))
#define popcount(n) (__builtin_popcountll(n))

using namespace std;

template<class T>bool chmax(T &a, const T &b) { return (a < b) ? (a = b, 1) : 0;}
template<class T>bool chmin(T &a, const T &b) { return (b < a) ? (a = b, 1) : 0;}

using ll = long long;
using R = long double;
const R EPS = 1e-9; // [-1000,1000]->EPS=1e-8 [-10000,10000]->EPS=1e-7
inline int sgn(const R& r) {return (r > EPS) - (r < -EPS);}
inline R sq(R x) {return sqrt(max<R>(x, 0.0));}

const int dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
const int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};

// Problem Specific Parameter:

//Appropriately Changed
using W = ll;
using edge = struct {int to, rev; W cap, flow, cost;};
using G = vector<vector<edge>>;

//Appropriately Changed
void add_edge(G &graph, int from, int to, W cap, W cost) {
	graph[from].push_back({to, int(graph[to].size()) , cap , 0 , cost});
	graph[to].push_back({from, int(graph[from].size()) - 1, 0 , 0, -cost});
}

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
		for (int v = t; v != s; v = pv[v]) chmin(d, graph[pv[v]][pe[v]].cap - graph[pv[v]][pe[v]].flow);
		f -= d, res += d * dist[t];

		for (int v = t; v != s; v = pv[v]) {
			edge &e = graph[pv[v]][pe[v]];
			e.flow += d;
			graph[v][e.rev].flow -= d;
		}
	}
	return res;
}

int main(void) {
	int v, e, f;
	cin >> v >> e >> f;
	G graph(v);

	rep(i, e) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		add_edge(graph, a, b, c, d);
	}

	cout << primal_dual(graph, 0, v - 1, f) << endl;
	return 0;
}