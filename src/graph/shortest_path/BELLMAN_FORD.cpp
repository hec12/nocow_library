// Description: 任意コストのグラフに対する単一始点最短経路 
// TimeComplexity: $\mathcal{O}(EV)$
// Verifyed: AOJ GRL_1_B

bool negative_cycle=false;
auto bellman_ford(const G &graph,int s,W inf){
	using W=ll;
	int n=graph.size(),update;
	vector<W> dist(n,inf);dist[s]=0;

	rep(loop,n){
		update=false;
		rep(v,n) if(dist[v]!=inf) for(auto &e:graph[v]){
			if(chmin(dist[e.to],dist[v]+e.cost))
				update=true;
		}
		if(!update) break;
	}

	negative_cycle=update;
	return dist;
}