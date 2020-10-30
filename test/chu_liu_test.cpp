#include <bits/stdc++.h>
 
#define _overload(_1,_2,_3,name,...) name
#define _rep(i,n) _range(i,0,n)
#define _range(i,a,b) for(int i=int(a);i<int(b);++i)
#define rep(...) _overload(__VA_ARGS__,_range,_rep,)(__VA_ARGS__)
  
using namespace std;
 
template<class T>bool chmax(T &a, const T &b) { return (a<b)?(a=b,1):0;}
template<class T>bool chmin(T &a, const T &b) { return (b<a)?(a=b,1):0;}
 
 
using edge=struct{int to,cost;};
using G=vector<vector<edge>>;
 
void add_edge(G &graph,int from,int to,int cost){ 
    graph[from].push_back({to,cost});
}
 
G chu_liu(const G &graph,int root){
    using W=int; const W inf=1<<28;
    const int n=graph.size();

    vector<int> cost(n,inf),pv(n,-1);
    rep(v,n) for(auto &e:graph[v]) if(chmin(cost[e.to],e.cost)) pv[e.to]=v;
 	
    int led=-1,unuse=-1;
    vector<int> comp(n),used(n,-1);
    iota(begin(comp),end(comp),0);

    rep(v,n)if(used[v]== -1 and pv[v]!=-1 and v!=root){
        int cur=used[v]=v;
        for(cur=pv[cur]; cur!=root && used[cur] == -1; cur=pv[cur]) used[cur]=v;
 
        if(used[cur]!=v) continue;
    	led=cur,comp[cur]=cur,v=n; 
    	for(int w=pv[cur]; w != cur; w=pv[w]) comp[w]=cur;
    }
 
    G ngraph(n),ret(n);
    using E=tuple<int,int,int>; map<E,E> dict;

    if(led==-1){
      	rep(v,n) if(v!=root and pv[v]!=-1)add_edge(ret,pv[v],v,cost[v]);
    }else{
		rep(v,n) for(auto &e:graph[v]){
			int a=comp[v],b=comp[e.to],c=e.cost-(comp[e.to]==led)*cost[e.to];
			if(a==b) continue;
			dict[E(a,b,c)]=E(v,e.to,e.cost);
			add_edge(ngraph,a,b,c);
		}
		
		G ntree=chu_liu(ngraph,comp[root]);

		rep(v,n) for(auto &e:ntree[v]){
			int a,b,c;
			tie(a,b,c)=dict[E(v,e.to,e.cost)];
			if(comp[b]==led) unuse=b;
			add_edge(ret,a,b,c);
		}

		rep(v,n) if(comp[v]==led and v!=unuse) add_edge(ret,pv[v],v,cost[v]);
	}
    return ret;
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
 
    auto tree=chu_liu(graph,r);
    int ans=0;
    rep(i,v) for(auto &e:tree[i]) ans+=e.cost;
    cout << ans << endl;
    return 0;
}