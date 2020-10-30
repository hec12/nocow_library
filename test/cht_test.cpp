#include <bits/stdc++.h>
 
#define _overload(_1,_2,_3,name,...) name
#define _rep(i,n) _range(i,0,n)
#define _range(i,a,b) for(int i=int(a);i<int(b);++i)
#define rep(...) _overload(__VA_ARGS__,_range,_rep,)(__VA_ARGS__)
 
#define _rrep(i,n) _rrange(i,n,0)
#define _rrange(i,a,b) for(int i=int(a)-1;i>=int(b);--i)
#define rrep(...) _overload(__VA_ARGS__,_rrange,_rrep,)(__VA_ARGS__)
 
#define _all(arg) begin(arg),end(arg)
 
template<class T>bool chmax(T &a, const T &b) { return (a<b)?(a=b,1):0;}
template<class T>bool chmin(T &a, const T &b) { return (b<a)?(a=b,1):0;}
 
using namespace std;
using ll=long long;
 
// Description: DP using Convex hull Trick
// TimeComplexity: $ \mathcal{O}(n)$ 
// Verifyed: AOJ 2725

//Inequality sign min >=  max <=
template<typename T> class CHT{
    public:
        T getval(T x){
            while(deq.size()>=2 && f(deq[0],x)<=f(deq[1],x)) deq.pop_front();
            return f(deq[0],x);
        }

        void push(T ca,T cb){
            const int idx=a.size();
            a.push_back(ca),b.push_back(cb);
            while(deq.size()>=2 && check(idx)) deq.pop_back();
            deq.push_back(idx);
        } 

        int size(){return deq.size();}
    private:
        vector<T> a,b;
        deque<int> deq;

        T f(int idx,T x){return 1LL*a[idx]*x+b[idx];}

        bool check(int idx){
            const int i=deq[size()-2],j=deq[size()-1],k=idx;
            return (b[j]-b[i])*(a[k]-a[j])<=(b[k]-b[j])*(a[j]-a[i]);
        }
};

ll t[4010],p[4010],f[4010];
ll dp[4010][4010];
CHT<ll> cht[4010];
 
inline ll sq(ll n){return n*n;}
 
int main(void){
    ll N,T;
    cin >> N >> T;
 
    vector<tuple<ll,ll,ll>> ary(N);
    rep(i,N){
        ll tt,pp,ff;
        cin >> tt >> pp >> ff;
        ary[i]=make_tuple(ff,tt,pp);
    }
 
    sort(_all(ary));
    rep(i,N) tie(f[i],t[i],p[i])=ary[i];
         
    rep(i,1,N+1)rrep(j,T+1,t[i-1]){
        bool ok=true;
        if(j==t[i-1]){
            chmax(dp[i][j],p[i-1]);
        }else if(j>t[i-1]){
            const ll base=j-t[i-1];
            if(cht[base].size()==0) ok=false;
            if(ok) chmax(dp[i][j],p[i-1]-sq(f[i-1])+cht[base].getval(f[i-1]));
            
            
        }

        if(ok==false) continue;
        const ll base=j;
        cht[base].push(2LL*f[i-1],-1LL*sq(f[i-1])+1LL*dp[i][j]);
    }
    
    ll ans=0LL;
    rep(i,N+1) rep(j,T+1) chmax(ans,dp[i][j]);
    cout << ans << endl;
 
    return 0;
}