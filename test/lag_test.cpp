#include <bits/stdc++.h>

#define _overload(_1,_2,_3,name,...) name
#define _rep(i,n) _range(i,0,n)
#define _range(i,a,b) for(int i=int(a);i<int(b);++i)
#define rep(...) _overload(__VA_ARGS__,_range,_rep,)(__VA_ARGS__)

#define _rrep(i,n) _rrange(i,n,0)
#define _rrange(i,a,b) for(int i=int(a)-1;i>=int(b);--i)
#define rrep(...) _overload(__VA_ARGS__,_rrange,_rrep,)(__VA_ARGS__)

#define _all(arg) begin(arg),end(arg)
#define uniq(arg) sort(_all(arg)),(arg).erase(unique(_all(arg)),end(arg))
#define getidx(ary,key) lower_bound(_all(ary),key)-begin(ary)
#define clr(a,b) memset((a),(b),sizeof(a))
#define bit(n) (1LL<<(n))
#define popcount(n) (__builtin_popcountll(n))

using namespace std;

template<class T>bool chmax(T &a, const T &b) { return (a<b)?(a=b,1):0;}
template<class T>bool chmin(T &a, const T &b) { return (b<a)?(a=b,1):0;}

using ll=long long;
using R=long double;
const R EPS=1e-5; // [-1000,1000]->EPS=1e-8 [-10000,10000]->EPS=1e-7
inline int sgn(const R& r){return(r > EPS)-(r < -EPS);}
inline R sq(R x){return sqrt(max<R>(x,0.0));}

const int dx[8]={1,0,-1,0,1,-1,-1,1};
const int dy[8]={0,1,0,-1,1,1,-1,-1};

// Problem Specific Parameter:

R Lagrange_interpolation(vector<R> xi,vector<R> fi,R x){
	const int n=xi.size();
	R f=0.0;
	rep(i,n){
		R li=1.0;
		rep(j,n){
			if(i==j) continue;
			li*=(x-xi[j])/(xi[i]-xi[j]);
		}
		f+=fi[i]*li;
	}
	return f;
}

int main(void){
	int d;
	while(cin >> d,d){
		vector<R> v(d+3);
		rep(i,d+3) cin >> v[i];
		
		int ans=-1;
		rep(j,d+3)rep(i,j){
			vector<R> x,f;
			rep(k,d+3){
				if(k==i||k==j) continue;
				x.push_back(k);
				f.push_back(v[k]);
			}

			R fi=Lagrange_interpolation(x,f,i);
			R fj=Lagrange_interpolation(x,f,j);

			if(sgn(v[i]-fi)==0) ans=j;
			if(sgn(v[j]-fj)==0) ans=i;
		}

		cout << ans << endl;
	}
	return 0;
}