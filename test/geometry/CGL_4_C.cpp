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

P cross(L a,L b){
	R u=det(a.s,b.s,b.t)/det(0,vec(a),vec(b));
	return (1-u)*a.s+u*a.t;
}

// Polygon
#define at(a,i) (a[(i + a.size()) % a.size()])

R area(const VP& pol){
	R sum=0.0;
	rep(i,pol.size()) sum+=det(0,at(pol,i),at(pol,i+1));
	return abs(sum/2.0L);
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
	int n,q;
	cin >> n;
	VP pol;
	rep(i,n){
		P p;
		cin >> p;
		pol.push_back(p); 
	}
	cin >> q;
	cout.precision(20);
	rep(i,q){
		P a,b;
		cin >> a >> b;
		L l={a,b};
		cout << fixed <<  area(convex_cut(pol,l)) << endl;
	}
	return 0;
}