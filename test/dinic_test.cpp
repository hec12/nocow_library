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

// Description: グラフの型定義(これは最小費用流)
// Verifyed: Many Diffrent Problem 

//Appropriately Changed
using edge=struct{int to,cap,rev;};
using G=vector<vector<edge>>;

//Appropriately Changed
void add_edge(G &graph,int from,int to,int cap){ 
	graph[from].push_back({to,cap,int(graph[to].size())});
	graph[to].push_back({from,0,int(graph[from].size())-1});
}

// Description: グラフに対する最大流 
// TimeComplexity: $ \mathcal{O}(EV^2) $ 
// Verifyed: AOJ GRL_6_A

template <typename W> W dinic(G &graph,int s,int t,W inf){
	const int n=graph.size();
	vector<int> level(n),iter(n);

	auto bfs=[&](int s,int t){
		fill(_all(level),-1);
		queue<int> q;
		level[s]=0,q.push(s);
		while(!q.empty()){
			int v=q.front();q.pop();
			for(auto &e:graph[v])
				if(e.cap>0 && level[e.to]<0)
					level[e.to]=level[v]+1,q.push(e.to);
		}
		return level[t]>=0;
	};

	auto dfs=[&](int v,int t,W f){
        auto func=[&](int v,int t,W f,auto func)->W{
        	if(v==t) return f;
			for(int &i=iter[v];i<graph[v].size();i++){
				edge &e=graph[v][i];
				if(e.cap>0 && level[v]<level[e.to]){
					W d=func(e.to,t,min<W>(f,e.cap),func);
					if(d==0) continue;
					e.cap-=d,graph[e.to][e.rev].cap+=d;
					return d;
				}
			}
			return 0;
        };
        return func(v,t,f,func);
    };

	W res=0;
	while(bfs(s,t)){
		fill(_all(iter),0);
		for(W f;f=dfs(s,t,inf);res+=f);
	}
	return res;
}

int main(void){
	int v,e;
	cin >> v >> e;
	G graph(v);
	rep(i,e){
		int a,b,c;
		cin >> a >> b >> c;
		add_edge(graph,a,b,c);
	}
	cout << dinic(graph,0,v-1,inf) << endl;
	return 0;
}