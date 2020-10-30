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

// convex_hull Verify AOJ CGL_4_A
VP convex_hull(VP pol){
	int n=pol.size(),k=0,t=1;
	
	auto cmp_x=[](P a,P b)->bool{
		int sr = sgn(real(a-b)), si=sgn(imag(a-b));
		return sr ? sr < 0:si < 0;
	};

	sort(begin(pol),end(pol),cmp_x);
	VP res(2*n);

	auto push = [&](P p)->void{
		while(k>t and sdet(res[k-1],res[k-2],p)<=-1) k--;
		res[k++]=p;
	};

	for_each(begin(pol),end(pol),push);
	t = k;
	for_each(rbegin(pol)+1,rend(pol),push);
	res.resize(k-1);
	return res;
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
	VP res=convex_hull(pol);
	int m=res.size(),idx=0;
	rep(i,m){
		if(imag(res[i])<imag(res[idx])) idx=i;
		if(imag(res[i])==imag(res[idx])&&real(res[i])<real(res[idx])) idx=i;
	}
	cout << m << endl;
	rep(i,m) cout << res[(idx-i+m)%m] << endl;
	return 0;
}