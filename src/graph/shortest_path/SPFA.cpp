//SPFA
bool spfa(const G &graph,int s){
	int n=graph.size();
	vector<W> dist(n,inf);dist[s]=0;
	vector<int> used(n,false); used[s]=true;
	queue<int>q;
	q.push(s);
	
	while(!q.empty()){
		int v=q.front();q.pop();
		used[v]=false;
		for(auto &e:graph[v]){
			if(chmin(dist[e.to],dist[v]+e.cost)){
				if(used[e.to]==false){
					used[e.to]=true;
					q.push(e.to);
				}
			}
		}
	}

	if(update) return false;
	return true;
}