const int vmax=5010;
struct node{int to;R cost;};
vector<node> graph[vmax];

// Points not verify
R toRagian(R degree){ return degree*PI/180.0;}
R ang (P p){return arg(p);}
R ang (P bs,P a,P b) {R res=arg((b-bs)/(a-bs));return res<0?res+2*PI:res;} 
P rot (P bs,P a,R tht){P tar=a-bs;return bs+polar(abs(tar),arg(tar)+tht);}

const int vmax=5010;
struct node{int to;R cost;};
vector<node> graph[vmax];

inline void add_edge(int f,int t,R c){reg(graph[f],{t,c}),reg(graph[t],{f,c});}

// AOJ 1352

void circle_arrangement(const VC &circle,VP &point){
	VP candiate;	
	auto can=[&](P p){
		for(auto &c:circle)if(icp(c,p,1)) return; 
		reg(candiate,p);
	};
	
	auto check1=[&](P p){
		for(auto &c:circle)if(icp(c,p,1)) return false; 
		return true;
	};
	
	auto check2=[&](L s){
		for(auto &c:circle)if(ics(c,s,1)) return false; 
		return true;
	};

	for(auto &c1:circle){
		rep(j,4) can(cir(c1,j*PI/2.0));
		for(auto &p:point) for(auto &l:tan(c1,p)) can(proj(l,c1.c));
		for(auto &c2:circle){
			if(rcc(c1,c2)==ISC) for(auto &p:pcc(c1,c2)) can(p);
			for(auto &l:tan(c1,c2)) can(proj(l,c1.c)),can(proj(l,c2.c));
		}
	}
	
	uniq(candiate),move(_all(candiate),back_inserter(point));
	for(auto &c:circle){
		vector<pair<R,int>> idx;
		rep(i,point.size()){
			if(sgn(norm(c.c-point[i])-norm(c.r))==0) 
				reg(idx,{arg(point[i]-c.c),i});
		}
		sort(_all(idx)),reg(idx,{idx[0].first+2*PI,idx[0].second});
		rep(i,1,idx.size()){
			R a1=idx[i-1].first,a2=idx[i].first;
			P mid=cir(c,(a1+a2)/2.0);
			if(check1(mid)) add_edge(idx[i-1].second,idx[i].second,c.r*(a2-a1));
		}
	}
	rep(i,point.size())rep(j,i){
		L l={point[i],point[j]};
		if(check2(l)) add_edge(i,j,abs(l.t-l.s));
	}
}
