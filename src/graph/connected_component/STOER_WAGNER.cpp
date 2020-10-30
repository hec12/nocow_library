const int vmax=210;
int graph[vmax][vmax];

// Stoer-Wagner Uva 10989

int minimum_cut(int n){
	int h[vmax][vmax];
	rep(i,n)rep(j,n) h[i][j]=graph[i][j];
	vi vertex(n);rep(i,n) vertex[i]=i;

	int cut=inf;
	for(int m=n;m>1;m--){
		vi ws(m,0);
		int cur=-1,prev=-1;
		int w;
		rep(loop,m){
			prev=cur;
			cur=max_element(ws.begin(),ws.end())-ws.begin();
			w=ws[cur];ws[cur]=-1;
			rep(i,m) if(ws[i]>=0) ws[i]+=h[vertex[cur]][vertex[i]];
			//併合によるコスト加算
		}
		rep(i,m){
			// prevにcurを併合
			h[vertex[i]][vertex[prev]]+=h[vertex[i]][vertex[cur]];
			h[vertex[prev]][vertex[i]]+=h[vertex[cur]][vertex[i]];
		}
		vertex.erase(vertex.begin()+cur);
		cut=min(cut,w);
	}
	return cut;
}