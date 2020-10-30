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
const R EPS=1e-9; // [-1000,1000]->EPS=1e-8 [-10000,10000]->EPS=1e-7
inline int sgn(const R& r){return(r > EPS)-(r < -EPS);}
inline R sq(R x){return sqrt(max<R>(x,0.0));}

const int dx[8]={1,0,-1,0,1,-1,-1,1};
const int dy[8]={0,1,0,-1,1,1,-1,-1};

// Problem Specific Parameter:
const int limit=200000;

// Description: [1,x]のクエリに対するデータ構造 
// TimeComplexity: 更新$\mathcal{O}(\log n)$ クエリ$\mathcal{O}(\log n)$
// Verifyed: ARC 033 C

template <typename T> class Binary_indexed_tree{
	public:
	    Binary_indexed_tree(int _n):n(_n){data.assign(n+1,0);}
	    
	    void update(int i,T x){
	    	for(;i<=n;i+=i&-i) data[i]+=x;
	    }

	    T query(int i){
	    	T ret=0;
	    	for(;i>0;i-=i&-i) ret+=data[i];
	    	return ret;
	    }

	    int lower_bound(T x) {
			if(x<=0) return 0;
			int i=0;
			for(int k=bit(31-__builtin_clz(n));k>0;k>>=1){
				if(i+k<=n && data[i+k]<x)
					x-=data[i+k],i+=k;
			}
			return i+1;
		}
		
	private:
		vector<T> data;
		int n;
};

int main(void){
	Binary_indexed_tree<int> Bit(limit);
	int q;
	cin >> q;
	rep(loop,q){
		int t,x;
		cin >> t >> x;
		if(t==1){
			Bit.update(x,1);
		}else{
			int ans=Bit.lower_bound(x);
			cout << ans << endl;
			Bit.update(ans,-1);
		}
	}
	return 0;
}