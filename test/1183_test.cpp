#include <bits/stdc++.h>

#define _overload(_1,_2,_3,name,...) name
#define _rep(i,n) _range(i,0,n)
#define _range(i,a,b) for(int i=int(a);i<int(b);++i)
#define rep(...) _overload(__VA_ARGS__,_range,_rep,)(__VA_ARGS__)

using namespace std;

template<class T>bool chmin(T &a, const T &b) { return (b<a)?(a=b,1):0;}

using R=long double;
const R EPS=1e-9L;
inline int sgn(const R& r){return(r > EPS)-(r < -EPS);}
inline R sq(R x){return sqrt(max(x,0.0L));}

const R INF = 1E40L;
using P=complex<R>;
using L=struct{P s,t;};
using VP=vector<P>;
using C=struct{P c;R r;};

auto& operator >> (istream& is,P& p){ R x,y;is >> x >> y; p=P(x,y); return is;}
auto& operator << (ostream& os,P& p){ os << real(p) << " " << imag(p); return os;}

inline R det(P o,P a,P b){return imag(conj(a-o)*(b-o));}
inline int sdet(P o,P a,P b){return sgn(det(o,a,b));}

P proj(L l,P p){ R u=real((p-l.s)/(l.t-l.s)); return (1-u)*l.s+u*l.t;}

bool iss(L a,L b){
    int sa=sdet(a.s,a.t,b.s)*sdet(a.s,a.t,b.t);
    int sb=sdet(b.s,b.t,a.s)*sdet(b.s,b.t,a.t);
    return max(sa,sb)<0;
}

VP cross(C c, L l){
    P h=proj(l,c.c),e=polar(sq(norm(c.r)-norm(h-c.c)),arg(l.t-l.s));
    return VP{h-e,h+e};
}

VP cross(C a,C b){
    P d=b.c-a.c,w=(norm(d)+norm(a.r)-norm(b.r))/(2.0L*norm(d))*d;
    return cross(a,{a.c+w,a.c+w+1il*w});
}

int n,m;
R cost[210][210];
C c[110];
L l[110];
P p[210];
 
inline int conv(int i){
    if(i==0) return -1;
    if(i==m-1) return n-1;
    return (i-1)/2;
}
 
int main(void){
    while(cin >> n,n){
        m=2*n;
        rep(i,m)rep(j,m) cost[i][j]=((i==j)?0:INF);
 
        rep(i,n) cin >> c[i].c >> c[i].r;
        
        p[0]=c[0].c;
        rep(i,n-1){
            VP res=cross(c[i],c[i+1]);
            p[2*i+1]=res[0];
            p[2*i+2]=res[1];
            l[i]=L{res[0],res[1]};
        }
        p[m-1]=c[n-1].c;
 
        rep(j,m)rep(i,j){
            L tar=L{p[i],p[j]};
 
            bool ok=true;             
            for(int k=conv(i)+1;k<conv(j);k++){
                if(iss(tar,l[k])==false)
                    ok=false;
            }
            if(ok) cost[i][j]=cost[j][i]=abs(p[i]-p[j]);
        }
        rep(k,m)rep(i,m)rep(j,m) chmin(cost[i][j],cost[i][k]+cost[k][j]);
         
        cout.precision(9);
        cout << fixed << cost[0][m-1] << endl;
    }
    return 0;
}