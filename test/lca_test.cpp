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

// Description: 木に対する最小共通祖先  
// TimeComplexity: Init $ \mathcal{O}(N) $ Query:$ \mathcal{O}(\log V)$
// Verifyed: AOJ GRL_5_C
 
auto init(const G& graph){
    const int n=graph.size(),logn=32-__builtin_clz(n);
    vector<vector<int>> par(logn,vector<int>(n));
    vector<int> depth(n);

    auto dfs=[&](int v,int p,int d){
        auto func=[&](int v,int p,int d,auto func)->void{
            par[0][v]=p,depth[v]=d;
            for(auto &e:graph[v]) if(e.to!=p) func(e.to,v,d+1,func);
        };
        return func(v,p,d,func);
    };

    dfs(0,-1,0);
    rep(k,logn-1)rep(v,n){
        par[k+1][v]=-1;
        if(par[k][v]!=-1) par[k+1][v]=par[k][par[k][v]];
    }
    return make_tuple(par,depth);
}

int lca(const auto &par,const auto &depth,int u,int v){
    const int logn=par.size();
    if(depth[u]<depth[v]) swap(u,v);
    rrep(k,logn) if((depth[u]-depth[v])>>k&1) u=par[k][u];
    if(u==v) return u;
    rrep(k,logn) if(par[k][u]!=par[k][v])u=par[k][u],v=par[k][v];
    return par[0][u];
}

int main(void){
	int n;
	cin >> n;
	G graph(n);

	rep(v,n){
        int k;
        cin >> k;
        rep(j,k){
            int c;
            cin >> c;
            add_edge(graph,v,c);
        }
	}

    vector<vector<int>> par;
    vector<int> depth;
    tie(par,depth)=init(graph);

    int q;
    cin >> q;
    rep(loop,q){
        int a,b;
        cin >> a >> b;
        cout << lca(par,depth,a,b) << endl;
    }
	return 0;
}