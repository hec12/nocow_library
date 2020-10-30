#include <bits/stdc++.h>

#define _overload(_1,_2,_3,name,...) name
#define _rep(i,n) _range(i,0,n)
#define _range(i,a,b) for(int i=int(a);i<int(b);++i)
#define rep(...) _overload(__VA_ARGS__,_range,_rep,)(__VA_ARGS__)

#define _all(arg) begin(arg),end(arg)
#define uniq(arg) sort(_all(arg)),(arg).erase(unique(_all(arg)),end(arg))

using namespace std;

template<class T>void reg(vector<T> &ary,const T &elem){ary.emplace_back(elem);}
template<class T>bool chmin(T &a, const T &b) {return (b<a)?(a=b,1):0;}

using R=long double;
const R EPS=1e-9L; // [-1000,1000]->EPS=1e-8 [-10000,10000]->EPS=1e-7
inline int sgn(const R& r){return(r > EPS)-(r < -EPS);}
inline R sq(R x){return sqrt(max(x,0.0L));}

const R INF = 1E40L;
const R PI = acos(-1.0L);
using P=complex<R>;
const P O=0.0L;
using L=struct{P s,t;};
using VL=vector<L>;
using VP=vector<P>;

inline R dot(P o,P a,P b){return real(conj(a-o)*(b-o));}
inline R det(P o,P a,P b){return imag(conj(a-o)*(b-o));}
inline int sdot(P o,P a,P b){return sgn(dot(o,a,b));}
inline int sdet(P o,P a,P b){return sgn(det(o,a,b));}

//projection verify AOJ CGL_1_A
P proj(L l,P p){ R u=real((p-l.s)/(l.t-l.s)); return u*l.s+(1-u)*l.t;}

bool parallel(L a,L b) {return sdet(O,a.t-a.s,b.t-b.s)==0;}
bool eql(L a,L b){ return parallel(a,b) and sdet(a.s,a.t,b.s)==0;}

bool iss(L a,L b){
	int sa=sdet(a.s,a.t,b.s)*sdet(a.s,a.t,b.t);
	int sb=sdet(b.s,b.t,a.s)*sdet(b.s,b.t,a.t);
	return max(sa,sb)<0;
}

P cross(L a,L b){
	R u=det(a.s,b.s,b.t)/det(O,a.t-a.s,b.t-b.s);
	return (1-u)*a.s+u*a.t;
}
	
VP convex_cut(const VP& pol,const L& l) {
	VP res;
	int n=pol.size();
	rep(i,n){
		P a = pol[i],b=pol[(i+1)%n];
		int da=sdet(l.s,l.t,a),db=sdet(l.s,l.t,b);
		if(da>=0) res.emplace_back(a);
		if(da*db<0) res.emplace_back(cross({a,b},l));
	}
	return res;
}

using edge=struct{int to; R cost;};
using G=vector<vector<edge>>;

void add_edge(G &graph,int from,int to,R cost){ 
	graph[from].push_back({to,cost});
	graph[to].push_back({from,cost});
}

namespace std{
	bool operator <  (const P& a,const P& b){ return sgn(real(a-b))?real(a-b)<0:sgn(imag(a-b))<0;}
	bool operator == (const P& a,const P& b){ return sgn(real(a-b))==0 && sgn(imag(a-b))==0;}
}

G segment_arrangement(const vector<L> &seg, vector<P> &point){
	int n=seg.size();
	rep(i,n){
		auto &l=seg[i];
		point.emplace_back(l.s);
		point.emplace_back(l.t);
		rep(j,i) if(iss(l,seg[j])) point.emplace_back(cross(l,seg[j]));
	}

	uniq(point);
	int m=point.size();
	G graph(m);
	
	for(auto &l:seg){
		vector<int> idx;
		rep(j,m) if(sdot(point[j],l.s,l.t)<0)  idx.emplace_back(j);
		
		sort(_all(idx),[&](int i,int j){return norm(point[i]-l.s)<norm(point[j]-l.s);});
		rep(j,1,idx.size()){
			int a=idx[j-1],b=idx[j];
			add_edge(graph,a,b,abs(point[a]-point[b]));
		}
	}
	return graph;
}

L bisector(P a, P b){
	const P mid=(a+b)/P(2,0);
	return L{mid, mid+(b-a)*P(0,1)};
}

VP voronoi_cell(VP pol,VP v,int s){
	rep(i,v.size()){
		if(i==s) continue;
		pol=convex_cut(pol,bisector(v[s],v[i]));
	}
	return pol;
}

auto dijkstra(const G &graph,const VP &point){
	using W=R;
    const int n=graph.size();
    vector<W> dist(n,INF);
    using state=tuple<W,int>;
    priority_queue<state,vector<state>,greater<state>> q;
    rep(s,n) if(sgn(real(point[s]))==0) dist[s]=0,q.push(state(0,s));
	    
    while(!q.empty()){
        W c; int v;
        tie(c,v)=q.top();q.pop();
        for(auto &e:graph[v]){
            W nc=c+e.cost; int nv=e.to;
            if(chmin(dist[nv],nc)) q.push(state(nc,nv));
        }
    }
    R res=INF;
	rep(t,n) if(sgn(real(point[t])-4.0)==0) chmin(res,dist[t]);
    return res;
}

int main(void){
	int n;
	while(cin >> n,n){
		VP pol={P(0,0),P(4,0),P(4,4),P(0,4)},vornoi,point;
		VL seg;
		
		rep(i,n){
			R x,y;
			cin >> x >> y;
			vornoi.emplace_back(P(x,y));
		}
	
		rep(i,n){
			VP res=voronoi_cell(pol,vornoi,i);
			for(auto &p:res) point.emplace_back(p);
			int m=res.size();
			rep(i,m){
				L l={res[i],res[(i+1)%m]};
				bool ok=true;
				rep(i,4) if(eql(l,{pol[i],pol[(i+1)%4]})) ok=false;
				if(ok) seg.emplace_back(l);
			}
		}
		G graph=segment_arrangement(seg,point);
		R res=dijkstra(graph,point);
		cout.precision(20);
		if(res>=INF)
			cout << "impossible" << endl;
		else
			cout << fixed << res << endl;
	}
	return 0;
}