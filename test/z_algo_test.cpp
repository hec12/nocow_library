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

// Description: Z[i]=sとs[i..]の最長共通部分列の長さ
// TimeComplexity: $\mathcal{O}(N)$ 
// Verifyed: ARC 060 D

auto z_algorithm(const string &s){
	int n=s.size(),i=1,j=0,k;
	vector<int> z(n,n);
	while(i<n){
		while(i+j<n&&s[i+j]==s[j]) j++;
		z[i]=j,k=!!j;
		while(i+k<n&&k+z[k]<j) z[i+k]=z[k],k++;
		i+=k+!j,j-=k;
	}
	return z;
}

int main(void){
	string s;
	cin >> s;
	const int n=s.size();

	bool same=true;
	for(auto &c:s) if(s[0]!=c) same=false;
	if(same){
		cout << int(s.size()) << endl;
		cout << 1 << endl;
		return 0;
	}

	auto Z1=z_algorithm(s);
	reverse(_all(s));
	auto Z2=z_algorithm(s);

	vector<int> G1(n+1,true),G2(n+1,true);

	for(int p=1;p<n;++p){
		if(G1[p]==false) continue;
		for(int k=2;(k-1)*p<=Z1[p];++k)
			G1[k*p]=false;
	}

	for(int p=1;p<n;++p){
		if(G2[p]==false) continue;
		for(int k=2;(k-1)*p<=Z2[p];++k)
			G2[k*p]=false;
	}

	if(G1[n]){
		cout << 1 << endl;
		cout << 1 << endl;
	}else{
		cout << 2 << endl;
		int ans=0;
		rep(i,1,n) if(G1[i]&&G2[n-i]) ans++;
		cout << ans << endl;
	}

	return 0;
}