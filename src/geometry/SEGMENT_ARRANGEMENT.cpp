// segments arrangement AOJ 1050
G segment_arrangement(const vector<L> &seg, vector<P> &point){
	int n=seg.size();
	rep(i,n){
		auto &l=seg[i];
		point.emplace_back({l.s,l.t});
		rep(j,i) if(iss(seg[i],seg[j],1)) point.emplace_back(cross(l,seg[j]));
	}

	uniq(point);
	int m=point.size();
	G graph(m);
	
	for(auto &l:seg){
		vector<int> idx;
		rep(j,m) if(sdot(point[j],l.s,l.t)<0)  idx.emplace_back(j);
		
		sort(_all(idx),[&](int i,int j){return norm(point[i]-l.s)<norm(point[j]-l.s)});
		rep(j,1,idx.size){
			int a=idx[j-1],b=idx[j];
			add_edge(graph,a,b,abs(point[a]-point[b]));
		}
	}
	return graph;
}
