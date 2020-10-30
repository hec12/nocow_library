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

//reflection verify AOJ CGL_1_B
P refl(L l,P p){return 2.0L*proj(l,p)-p;}

// CCW verify AOJ CGL_1_C
enum CCW{ LEFT = 1,RIGHT = 2,BACK = 4,FRONT = 8,ON = 16};
inline int ccw(P o,P a,P b) {
	if(sdet(o,a,b) > 0) return LEFT;    // counter clockwise
	if(sdet(o,a,b) < 0) return RIGHT;   // clockwise
	if(sdot(o,a,b) < 0) return BACK;    // b--base--a on line
	if(sgn(norm(a-o)-norm(b-o)) < 0) return FRONT;   // base--a--b on line
	return ON; // base--b--a on line  semnet determination betwenn a and b 
}

int main(void){
	P a,b,p;
	int n;
	cin >> a >> b >> n;
	rep(i,n){
		cin >> p;
		int res=ccw(a,b,p);
		if(res==LEFT) cout << "COUNTER_CLOCKWISE" << endl;
		if(res==RIGHT) cout << "CLOCKWISE" << endl;
		if(res==BACK) cout << "ONLINE_BACK" << endl;
		if(res==FRONT) cout << "ONLINE_FRONT" << endl;
		if(res==ON) cout << "ON_SEGMENT" << endl;
	}
	return 0;
}