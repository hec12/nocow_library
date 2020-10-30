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
	if(sdot(l.s,l.t,p)) h=l.s;
	if(sdot(l.t,l.s,p)) h=l.t;
	return abs(p-h);
}

R dss(L a,L b){return iss(a,b)?0:min({dsp(a,b.s),dsp(a,b.t),dsp(b,a.s),dsp(b,a.t)});}

int main(void){
	int n;
	cin >> n;
	cout.precision(20);
	rep(i,n){
		P a,b,c,d;
		cin >> a >> b >> c >> d;
		L s1={a,b},s2={c,d};
		if(parallel(s1,s2))
			cout << 2 << endl;
		else if(vertical(s1,s2))
			cout << 1 << endl;
		else
			cout << 0 << endl;
	}
	return 0;
}