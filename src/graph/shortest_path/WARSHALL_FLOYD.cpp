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