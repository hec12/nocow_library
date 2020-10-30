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

template<class T>bool chmax(T &a, const T &b) { return (a<b)?(a=b,1):0;}
template<class T>bool chmin(T &a, const T &b) { return (b<a)?(a=b,1):0;}

using ll=long long;
using R=long double;
const R EPS=1e-9; // [-1000,1000]->EPS=1e-8 [-10000,10000]->EPS=1e-7
inline int sgn(const R& r){return(r > EPS)-(r < -EPS);}
inline R sq(R x){return sqrt(max<R>(x,0.0));}

const int dx[8]={1,0,-1,0,1,-1,-1,1};
const int dy[8]={0,1,0,-1,1,1,-1,-1};

// Problem Specific Parameter:

//Appropriately Changed
using edge=struct{int to,cost;};
using G=vector<vector<edge>>;

//Appropriately Changed
void add_edge(G &graph,int from,int to,int cost){ 
	graph[from].push_back({to,cost});
}

auto chuliu(G &graph,int root){
	using W=int;
	const W inf=1<<28;
	int n=graph.size();
	
	vector<int> visit(n, -1);

	auto dfs=[&](int v){
        auto func=[&](int v,auto func)->int{
            int res=1;
			visit[v]=1;
			for(auto e:graph[v]) if(visit[e.to]==-1) res+=func(e.to,func);
			return res;
	    };
        return func(v,func);
    };

    if(dfs(root)!= n) return inf;

    // Construct a reversed graph
	G rev(n);
	rep(v,n) for(auto &e:graph[v]) add_edge(rev,e.to,v,e.cost);

	vector<int> active(n, true);
	W cost=0;
	while(1){
		vector<W>  min_cost(n,inf);
		vector<int> min_prev(n),visit(n, -1);

		rep(v,n){
			for(auto &e:rev[v]){
				if (v != root && active[v] && active[e.to] && chmin(min_cost[v],e.cost))
					min_prev[v] = e.to;
			}
		}

		bool has_cycle = false;

		rep(u,n){
			if (visit[u] != -1 || !active[u] || u == root) continue;
			int v = visit[u] = u;
			for(v = min_prev[v]; v != root && visit[v] == -1; v = min_prev[v]) visit[v] = u;

			if (visit[v] == u){
				vector<int> cycle_nodes;
				
				for (int w = v; cycle_nodes.empty() || w != v; w = min_prev[w]){
					active[w] = false;
					cycle_nodes.push_back(w);
				}

				active.push_back(true);
				rev.push_back(vector<edge>());
				graph.push_back(vector<edge>());

				for(int &v:cycle_nodes){
					cost += min_cost[v];
					for (const auto &e:rev[v]){
						if(active[e.to]){
							add_edge(rev,n,e.to, e.cost-min_cost[v]);
							add_edge(graph,e.to,n,e.cost-min_cost[v]);
						}
					}
					for (const auto &e:graph[v]){
						if (active[e.to]){
							add_edge(graph,n,e.to,e.cost);
							add_edge(rev,e.to,n,e.cost);
						} 
					}
				}
				has_cycle = true;
				n++;
			}
		}
		if(!has_cycle){
			rep(v,n) if (v != root && active[v]) cost += min_cost[v];
			return cost;
		}
	}
} 

int main(void){
	int v,e,r;
	cin >> v >> e >> r;
	G graph(v);
	rep(i,e){
		int a,b,w;
		cin >> a >> b >> w;
		add_edge(graph,a,b,w);
	}

	cout << chuliu(graph,r) << endl;
	return 0;
}
