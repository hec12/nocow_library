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

// Description: 任意コストのグラフに対する全点間最短経路 
// TimeComplexity: $\mathcal{O}(V^3)$
// Verifyed: AOJ GRL_1_C

bool negative_cycle=false;
template <typename W> auto Warshall_floyd(const auto &graph,W inf){
	vector<vector<W>> dist=graph;
	const int n=dist.size();
	rep(k,n)rep(i,n)rep(j,n){
		if(dist[i][k]!=inf && dist[k][j]!=inf)  
			chmin(dist[i][j],dist[i][k]+dist[k][j]);
	}
	rep(i,n) if(dist[i][i]<0) negative_cycle=true;
	return dist;
}

int main(void){
	int n,m;
	cin >> n >> m;
	vector<vector<ll>> graph(n,vector<ll>(n,inf));

	rep(i,n) graph[i][i]=0LL;

	rep(i,m){
		int a,b; ll c;
		cin >> a >> b >> c;
		graph[a][b]=c;
	}

	auto dist=Warshall_floyd<ll>(graph,inf);


	if(negative_cycle){
		cout << "NEGATIVE CYCLE" << endl;
	}else{
		rep(i,n){
			rep(j,n){
				if(dist[i][j]==inf)
					cout << (j?" ":"") << "INF";
				else
					cout << (j?" ":"") <<dist[i][j];
			}
			cout << endl;
		}
	}
	return 0;
}