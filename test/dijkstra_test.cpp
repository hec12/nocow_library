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
const ll inf=1LL<<50;

// Description: グラフの型定義
using edge=struct{int to;ll cost;};
using G=vector<vector<edge>>;

void add_edge(G &graph,int from,int to,ll cost){
	graph[from].push_back({to,cost});
}

//TimeComplexity $\mathcal{O}(E\log V)$
template <typename W> auto dijkstra(const G &graph,int s,W inf){
    const int n=graph.size();
    vector<W> dist(n,inf);
    using state=tuple<W,int>;
    priority_queue<state,vector<state>,greater<state>> q;
    dist[s]=0,q.push(state(0,s));
    
    while(!q.empty()){
        W c; int v;
        tie(c,v)=q.top();q.pop();
        for(auto &e:graph[v]){
            W nc=c+e.cost; int nv=e.to;
            if(chmin(dist[nv],nc)) q.push(state(nc,nv));
        }
    }
    return dist;
}

int main(void){
	int n,m,s;
	cin >> n >> m >> s;
	G graph(n);

	rep(i,m){
		int a,b; ll c;
		cin >> a >> b >> c;
		add_edge(graph,a,b,c);
	}

	auto dist=dijkstra<ll>(graph,s,inf);
	rep(i,n){
		if(dist[i]==inf)
			cout << "INF" << endl;
		else
			cout << dist[i] << endl;
	}
	return 0;
}