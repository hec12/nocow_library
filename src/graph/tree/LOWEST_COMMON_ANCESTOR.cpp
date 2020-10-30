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