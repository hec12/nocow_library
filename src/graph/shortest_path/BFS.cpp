auto bfs(const G &graph,int s,int inf){
    const int n=graph.size();
    vector<int> dist(n,inf);
 
    queue<int> q;
    dist[s]=0,q.push(s);
    
    while(!q.empty()){
        int v=q.front();q.pop();
        for(auto &e:graph[v]){
            int nc=dist[v]+1,nv=e.to;
            if(chmin(dist[nv],nc)) q.push(nv);
        }
    }
    return dist;
}