#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;(i)<(n);++(i))
using namespace std;

// Description: ベクトル
// Verifyed: various problem 
using namespace placeholders;
using R=long double;
const R EPS=1e-9L; // [-1000,1000]->EPS=1e-8 [-10000,10000]->EPS=1e-7
inline int sgn(const R& r){return(r > EPS)-(r < -EPS);}
inline R sq(R x){return sqrt(max(x,0.0L));}

const R INF = 1E40L;
const R PI = acos(-1.0L);
using P=complex<R>;
using L=struct{P s,t;};
using VP=vector<P>;
using C=struct{P c;R r;};

auto& operator >> (istream& is,P& p){ R x,y; is >> x >> y,p=P(x,y); return is;}
auto& operator << (ostream& os,P& p){ os << real(p) << " " << imag(p); return os;}

inline R dot(P o,P a,P b){return real(conj(a-o)*(b-o));}
inline R det(P o,P a,P b){return imag(conj(a-o)*(b-o));}
inline P vec(L l){return l.t-l.s;}
auto sdot = bind(sgn,bind(dot,_1,_2,_3));
auto sdet = bind(sgn,bind(det,_1,_2,_3));

//projection verify AOJ CGL_1_A
P proj(L l,P p){ R u=real((p-l.s)/vec(l)); return (1-u)*l.s+u*l.t;}

// vertical parallel
// verified: AOJ CGL_2_A
bool vertical(L a,L b) {return sdot(0,vec(a),vec(b))==0;}
bool parallel(L a,L b) {return sdet(0,vec(a),vec(b))==0;}
bool eql(L a,L b){ return parallel(a,b) and sdet(a.s,a.t,b.s)==0;}

// crossing determination
// verified: AOJ CGL_2_B 
bool iss(L a,L b){
	int sa=sdet(a.s,a.t,b.s)*sdet(a.s,a.t,b.t);
	int sb=sdet(b.s,b.t,a.s)*sdet(b.s,b.t,a.t);
	return max(sa,sb)<0;
}

// crossing point 
// verified: AOJ CGL_2_C
P cross(L a,L b){
	R u=det(a.s,b.s,b.t)/det(0,vec(a),vec(b));
	return (1-u)*a.s+u*a.t;
}
	
// distance 
// verified: AOJ CGL_2_D
R dsp(L l,P p){
	P h=proj(l,p);
	if(sdot(l.s,l.t,p)<=0) h=l.s;
	if(sdot(l.t,l.s,p)<=0) h=l.t;
	return abs(p-h);
}

R dss(L a,L b){return iss(a,b)?0:min({dsp(a,b.s),dsp(a,b.t),dsp(b,a.s),dsp(b,a.t)});}

// Polygon
#define at(a,i) (a[(i + a.size()) % a.size()])

// area 
// verified: AOJ 1100 CGL_3_A
R area(const VP& pol){
	R sum=0.0;
	rep(i,pol.size()) sum+=det(0,at(pol,i),at(pol,i+1));
	return abs(sum/2.0L);
}

// convex_polygon determination
// verified: CGL_3_B
bool is_convex(const VP& pol){
	rep(i,pol.size())if(sdet(at(pol,i),at(pol,i+1),at(pol,i+2))<0) return false;
	return true;
}

// polygon realation determination  in  2 on 1 out 0　(possible non-convex) 
// verified: AOJ CGL_3-C
int in_polygon(const VP& pol, const P& p){
	int res=0;
	auto simag = [](const P &p){return sgn(imag(p));};
	rep(i,pol.size()){
		P a=at(pol,i),b=at(pol,i+1);
		if(sdet(p,a,b)==0 and sdot(p,a,b)<=0) return 1;
		bool f=simag(p-a)>=0,s=simag(p-b)<0;
		if(simag(b-a)*sdet(a,b,p)==1 and f==s) res+=(2*f-1);
	}
	return res?2:0;
}

// polygon realation determination　(possible non-convex) 
// verified: not AOJ 2514
bool in_polygon(const VP& pol, const L& l){
	VP check={l.s,l.t};
	rep(i,pol.size()){
		L edge={at(pol,i),at(pol,i+1)};
		if(iss(l,edge)) check.emplace_back(cross(l,edge));
	}

	auto cmp_x=[](P a,P b)->bool{
		int sr = sgn(real(a-b)), si = sgn(imag(a-b));
		return sr ? sr < 0 :si < 0;
	};
	
	sort(begin(check),end(check),cmp_x);
	rep(i,check.size()-1){
		P m=(at(check,i)+at(check,i+1))/2.0L;
		if(in_polygon(pol,m)==false) return false;
	}
	return true;
}

// convex_cut 
// verified: AOJ CGL_4_C
VP convex_cut(const VP& pol,const L& l) {
	VP res;
	rep(i,pol.size()){
		P a = at(pol,i),b=at(pol,i+1);
		int da=sdet(l.s,l.t,a),db=sdet(l.s,l.t,b);
		if(da>=0) res.emplace_back(a);
		if(da*db<0) res.emplace_back(cross({a,b},l));
	}
	return res;
}

int main(void){
	int n;
	cin >> n;
	cout.precision(1);
	VP pol;
	rep(i,n){
		P p;
		cin >> p;
		pol.push_back(p); 
	}
	cout << fixed << area(pol) << endl;
	return 0;
}