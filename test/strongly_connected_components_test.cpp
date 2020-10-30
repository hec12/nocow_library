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

// Description: グラフの型定義(これは最小費用流)
// Verifyed: Many Diffrent Problem 

//Appropriately Changed
using edge=struct{int to;};
using G=vector<vector<edge>>;

//Appropriately Changed
void add_edge(G &graph,int from,int to){ 
	graph[from].push_back({to});
}

// Description: 有向グラフに対する強連結成分 
// TimeComplexity: $ \mathcal{O}(V + E) $
// Verifyed: AOJ GRL_3_C 

auto strongly_connected_components(const G& graph){
    int n=graph.size(),k=0;
    vector<int> par(n),ord(n,-1),low(n),scc(n,-1),res;
    stack<int> s;

    auto dfs=[&](int v,int p,int &k){
        auto func=[&](int v,int p,int &k,auto func)->void{
            ord[v]=k++,low[v]=ord[v],par[v]=p,s.push(v);
            for(auto &e:graph[v]){
                if(scc[e.to]!=-1) continue;
                if(ord[e.to]==-1)
                    func(e.to,v,k,func),chmin(low[v],low[e.to]);
                else
                    chmin(low[v],ord[e.to]);
            }
            if(ord[v]!=low[v]) return ;
            while(1){
                int u=s.top();s.pop();
                scc[u]=v;
                if(u==v) break;
            }
        };
        return func(v,p,k,func);
    };

    rep(v,n) if(ord[v]==-1) dfs(v,-1,k);
    return scc;     
}

int main(void){
	int v,e;
	cin >> v >> e;
	G graph(v);
	rep(i,e){
		int a,b;
		cin >> a >> b;
		add_edge(graph,a,b);
	}

	auto res=strongly_connected_components(graph);
	
    int q;
    cin >> q;
    rep(loop,q){
        int u,v;
        cin >> u >> v;
        cout << (res[u]==res[v]) << endl;
    }
	return 0;
}