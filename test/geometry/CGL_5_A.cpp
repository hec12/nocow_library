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

#define at(a,i) (a[(i + a.size()) % a.size()])

auto& operator >> (istream& is,P& p){ R x,y; is >> x >> y,p=P(x,y); return is;}
auto& operator << (ostream& os,P& p){ os << real(p) << " " << imag(p); return os;}

inline R dot(P o,P a,P b){return real(conj(a-o)*(b-o));}
inline R det(P o,P a,P b){return imag(conj(a-o)*(b-o));}
inline P vec(L l){return l.t-l.s;}
auto sdot = bind(sgn,bind(dot,_1,_2,_3));
auto sdet = bind(sgn,bind(det,_1,_2,_3));

//projection verify AOJ CGL_1_A
P proj(L l,P p){ R u=real((p-l.s)/vec(l)); return (1-u)*l.s+u*l.t;}

// closest point pair Verify AOJ CGL_5_A
R cpp(VP a,int flag=1){
	const int n=a.size(),m=n/2;
	if(n<=1) return INF;
	
	auto cmp_x=[](P a,P b)->bool{
		int sr = sgn(real(a-b)), si = sgn(imag(a-b));
		return sr ? sr < 0 :si < 0;
	};

	if(flag) sort(begin(a),end(a),cmp_x);
	
	VP b(begin(a),begin(a)+m),c(begin(a)+m,end(a));
	R x=real(a[m]),d=min(cpp(b,0),cpp(c,0));
	

	auto cmp_y=[](P a,P b)->bool{
		int sr = sgn(real(a-b)), si = sgn(imag(a-b));
		return si ? si < 0 :sr < 0;
	};

	sort(begin(a),end(a),cmp_y);
	deque<P> e;

	for(auto &p:a){
		if(abs(real(p)-x)>=d) continue;	
		
		for(auto &q:e){
			if(imag(p-q)>=d) break;
			d=min(d,abs(p-q));
		}
		e.push_front(p);
	}
	return d;
}

int main(void){
	int n;
	cin >> n;
	VP pol;
	rep(i,n){
		P p;
		cin >> p;
		pol.push_back(p);
	}
	cout.precision(20);
	cout << fixed << cpp(pol) << endl;
	return 0;
}