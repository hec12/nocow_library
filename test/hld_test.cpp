// Description: グラフの型定義(これは最小費用流)
// Verifyed: Many Diffrent Problem 

//Appropriately Changed
using edge=struct{int to,cost;};
using G=vector<vector<edge>>;

void add_edge(G &graph,int from,int to){ 
	graph[from].push_back({to});
	graph[to].push_back({from});
}

auto init(const G& graph){
	const int n=graph.size(),logn=32-__builtin_clz(n);
	vector<vector<int>> par(logn,vector<int>(n));
	vector<int> depth(n),sz(n);

	auto dfs=[&](int v,int p,int d){
		auto func=[&](int v,int p,int d,auto func)->void{
			sz[v]=1LL; par[0][v]=p,depth[v]=d;
			for(auto &e:graph[v]) if(e.to!=p) func(e.to,v,d+1,func),sz[v]+=sz[e.to];
		};
		return func(v,p,d,func);
	};

	dfs(0,-1,0);
	rep(k,logn-1)rep(v,n){
		par[k+1][v]=-1;
		if(par[k][v]!=-1) par[k+1][v]=par[k][par[k][v]];
	}
    return make_tuple(par,depth,sz);
}

auto hld(const G &graph){
	vector<int> par,depth,sz;
	tie(par,depth,sz)=init(graph);

	const int n=grpah.size();
	vector<vector<int>> chain(1);
	vector<int> idx(n),pos(n);
	int id=0;

	auto dfs=[&](int v,int p){
		auto func=[&](int v,int p,auto func)->void{
			idx[v]=id,pos[v]=chain[id].size();
			chain[id].push_back(v);
			int cmax=-1,u=-1;
			for(auto &v2:tree[v]){
				if(v2==p) continue;
				chmax(cmax,sz[v2]) u=v2;
			}
			if(u>=0) hld(u,v,id);
			for(auto &v2:tree[v]){
				if(v2==p||v2==u) continue;
				chain.push_back(vector<int>());
				hld(v2,v,++id);
			}
		};
		return func(v,p,func);
    };
    dfs(0,-1);
    return make_tuple(par,depth,sz,chain,idx,pos);
}

auto lca(const auto &par,const auto &depth,int u,int v){
    const int logn=par.size();
    bool swapped=false;
    if(depth[u]<depth[v]) swap(u,v),swapped=true;
    rrep(k,logn) if((depth[u]-depth[v])>>k&1) u=par[k][u];
    if(u==v) return make_pair(u,-1);
    rrep(k,logn) if(par[k][u]!=par[k][v])u=par[k][u],v=par[k][v];
    if(swapped) 
		return make_pair(par[0][v],u); 
    else
    	return make_pair(par[0][u],v);
}

SegmentTree<ll>* seg[nmax];

state opr(int t,int v, int root,int cost){
	state ret=make_tuple(-INF,0,-INF,-INF);
	while(1){
		int u=chain[idx[v]][0];
		if(depth[u]<=depth[root]) u=root;
		if(t==1)
			seg[idx[v]]->update(pos[u],pos[v]+1, cost);
		else
			ret=vmerge(seg[idx[v]]->query(pos[u],pos[v]+1),ret);
		if(u==root) break;
		v=parent[u][0];
	}
	return ret;
}

int n,q,w[nmax],k;

int main(void){
	/*
	cin >> n >> q;
	rep(i,n) cin >> w[i];
	rep(i,n-1){
		int a,b;
		cin >> a >> b;
		tree[a-1].push_back(b-1);
		tree[b-1].push_back(a-1);
	}
	dfs(0,-1,0);
	int m=hld(0,-1,k);

	rep(d,19)rep(i,n){
		if(parent[i][d]==-1)
			parent[i][d+1]=-1;
		else
			parent[i][d+1]=parent[parent[i][d]][d];
	}
	
	*/
	rep(i,m) seg[i]=new SegmentTree<ll>(chain[i].size(),-INF);
	rep(i,n) seg[idx[i]]->update(pos[i],pos[i]+1,w[i]);

	rep(loop,q){
		int t,a,b,c,u,v;
		cin >> t >> a >> b >> c;
		a--,b--;
		tie(u,v)=lca(a,b);
		if(v==a){
			state cur=opr(t,b,a,c);
			if(t==2) cout << get<0>(cur) << endl;
		}else{
			state left=opr(t,a,u,c),right=opr(t,b,v,c);
			swap(get<2>(left),get<3>(left));
			if(t==2) cout << get<0>(vmerge(left,right)) << endl;
		}
	}
	return 0;
}

int main(void){
	return 0;
}