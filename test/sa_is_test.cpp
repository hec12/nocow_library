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


#define is_lms(i) (i>0 && t[i] && !t[i-1])

void get_buckets(auto s,auto bkt,int n, int K, bool end=true) {
    int sum=0;
    rep(i,K+1) btk[i]=0;
    rep(i,n) bkt[s[i]]++; 
    rep(i,K+1) sum+=bkt[i],bkt[i]=(end?sum:sum-bkt[i]);
}

void induce_sal(auto t,auto sa, auto s,auto bkt,int n,int K) {
    get_buckets(s,bkt,n,K,false);
    rep(i,n){
        int j=sa[i]-1;
        if(j>=0 && !t[j]) sa[bkt[s[j]]++]=j;
    }
}

void induce_sas(auto t,auto sa,auto s,auto bkt,int n,int K){
    get_buckets(s,bkt,n,K,true); 
    rrep(i,n){
        int j=sa[i]-1;
        if(j>=0 && t[j]) sa[--bkt[s[j]]]=j;
    }
}

void rec(auto s,auto sa,int n,int K) {
    vector<bool> t(n,false);
    
    t[n-1]=1,t[n-2]=0;
    rrep(i,n-2) t[i]=(s[i]<s[i+1] || (s[i]==s[i+1] && t[i+1]==1));

    vector<int> bkt(K+1);
    get_buckets(s,bkt,n,K);

    rep(i,n) sa[i]=-1;
    rep(i,1,n) if(is_lms(i)) sa[--bkt[s[i]]]=i;

    induce_sal(t,sa,s,bkt,n,K);
    induce_sas(t,sa,s,bkt,n,K);

    int n1=0;
    rep(i,n) if(is_lms(sa[i])) sa[n1++]=sa[i];

    fill(sa+n1,sa+n,-1);
    int name=0,prev=-1;

    rep(i,n1){
        int pos=sa[i]; bool diff=false;
        rep(d,n){
            if(prev==-1 || s[pos+d]!=s[prev+d] || t[pos+d]!=t[prev+d])
                { diff=true; break; }
            else if(d>0 && (is_lms(pos+d) || is_lms(prev+d))) break;
        }
        if(diff) { name++; prev=pos; }
        pos=pos/2;
        sa[n1+pos]=name-1;
    }

    for(int i=n-1, j=n-1; i>=n1; i--) if(sa[i]>=0) sa[j--]=sa[i];

    auto sa1=sa,s1=sa+n-n1;
    
    if(name<n1) 
        rec(s1,sa1,n1,name-1);
    else
        rep(i,n1) sa1[s1[i]] = i;

    get_buckets(s,bkt,n,K);
    for(int i=1,j=0;i<n; i++) if(is_lms(i)) s1[j++]=i;

    rep(i,n1)  sa1[i]=s1[sa1[i]];
    fill(sa+n1,sa+n,-1);

    rrep(i,n1){
        int j=sa[i];
        sa[i]=-1,sa[--bkt[s[j]]]=j;
    }

    induce_sal(t,sa,s,bkt,n,K);
    induce_sas(t,sa,s,bkt,n,K);
}



unsigned char mask[]={0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
#define tget(i) ( (t[(i)/8]&mask[(i)%8])?1:0)
#define tset(i, b) t[(i)/8]=(b) ? (mask[(i)%8]|t[(i)/8]) : ((~mask[(i)%8])&t[(i)/8])
#define chr(i) (cs==sizeof(int)?((int*)s)[i]:((unsigned char *)s)[i])
#define isLMS(i) (i>0 && tget(i) && !tget(i-1))

// find the start or end of each bucket
void getBuckets(unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
  int i, sum=0;
  for(i=0; i<=K; i++) bkt[i]=0; // clear all buckets
  for(i=0; i<n; i++) bkt[chr(i)]++; // compute the size of each bucket
  for(i=0; i<=K; i++) { sum+=bkt[i]; bkt[i]=end ? sum : sum-bkt[i]; }
}

// compute SAl
void induceSAl(unsigned char *t, int *SA, unsigned char *s, int *bkt,
                int n, int K, int cs, bool end) {
  int i, j;
  getBuckets(s, bkt, n, K, cs, end); // find starts of buckets
  for(i=0; i<n; i++) {
      j=SA[i]-1;
      if(j>=0 && !tget(j)) SA[bkt[chr(j)]++]=j;
  }
}

// compute SAs
void induceSAs(unsigned char *t, int *SA, unsigned char *s, int *bkt,
                int n, int K, int cs, bool end) {
  int i, j;
  getBuckets(s, bkt, n, K, cs, end); // find ends of buckets
  for(i=n-1; i>=0; i--) {
      j=SA[i]-1;
      if(j>=0 && tget(j)) SA[--bkt[chr(j)]]=j;
  }
}

// find the suffix array SA of s[0..n-1] in {1..K}^n
// require s[n-1]=0 (the sentinel!), n>=2
// use a working space (excluding s and SA) of at most 2.25n+O(1) for a constant alphabet
void SA_IS(unsigned char *s, int *SA, int n, int K, int cs) {
  int i, j;
  unsigned char *t=(unsigned char *)malloc(n/8+1); // LS-type array in bits

  // Classify the type of each character
  tset(n-2, 0); tset(n-1, 1); // the sentinel must be in s1, important!!!
  for(i=n-3; i>=0; i--)
    tset(i, (chr(i)<chr(i+1) || (chr(i)==chr(i+1) && tget(i+1)==1))?1:0);

  // stage 1: reduce the problem by at least 1/2
  // sort all the S-substrings
  int *bkt = (int *)malloc(sizeof(int)*(K+1)); // bucket array
  getBuckets(s, bkt, n, K, cs, true); // find ends of buckets
  for(i=0; i<n; i++) SA[i]=-1;
  for(i=1; i<n; i++)
    if(isLMS(i)) SA[--bkt[chr(i)]]=i;

  induceSAl(t, SA, s, bkt, n, K, cs, false);
  induceSAs(t, SA, s, bkt, n, K, cs, true);
  free(bkt);

  // compact all the sorted substrings into the first n1 items of SA
  // 2*n1 must be not larger than n (proveable)
  int n1=0;
  for(i=0; i<n; i++)
    if(isLMS(SA[i])) SA[n1++]=SA[i];

  // find the lexicographic names of all substrings
  for(i=n1; i<n; i++) SA[i]=-1; // init the name array buffer
  int name=0, prev=-1;
  for(i=0; i<n1; i++) {
    int pos=SA[i]; bool diff=false;
    for(int d=0; d<n; d++)
      if(prev==-1 || chr(pos+d)!=chr(prev+d) || tget(pos+d)!=tget(prev+d))
      { diff=true; break; }
      else if(d>0 && (isLMS(pos+d) || isLMS(prev+d))) break;
    if(diff) { name++; prev=pos; }
    pos=(pos%2==0)?pos/2:(pos-1)/2;
    SA[n1+pos]=name-1;
  }
  for(i=n-1, j=n-1; i>=n1; i--)
      if(SA[i]>=0) SA[j--]=SA[i];

  // stage 2: solve the reduced problem
  // recurse if names are not yet unique
  int *SA1=SA, *s1=SA+n-n1;
  if(name<n1)
    SA_IS((unsigned char*)s1, SA1, n1, name-1, sizeof(int));
  else // generate the suffix array of s1 directly
    for(i=0; i<n1; i++) SA1[s1[i]] = i;

  // stage 3: induce the result for the original problem
  bkt = (int *)malloc(sizeof(int)*(K+1)); // bucket array
  // put all left-most S characters into their buckets
  getBuckets(s, bkt, n, K, cs, true); // find ends of buckets
  for(i=1, j=0; i<n; i++)
    if(isLMS(i)) s1[j++]=i; // get p1

  for(i=0; i<n1; i++) SA1[i]=s1[SA1[i]]; // get index in s
  for(i=n1; i<n; i++) SA[i]=-1; // init SA[n1..n-1]

  for(i=n1-1; i>=0; i--) {
      j=SA[i]; SA[i]=-1;
      SA[--bkt[chr(j)]]=j;
  }
  induceSAl(t, SA, s, bkt, n, K, cs, false);
  induceSAs(t, SA, s, bkt, n, K, cs, true);
  free(bkt); free(t);
}

/*
auto sa_is(const string &str){
    const int n=str.size();
    vector<int> s(n+1,0),sa(n+1),rnk(n+1,0);
    rep(i,n) s[i]=int(str[i]);
    rec(begin(s),begin(sa),n+1,255);
    rep(i,n+1) rnk[sa[i]]=i;
    return make_tuple(rnk,sa);
}


int main(void){
	unsigned char s[1000010];
	int sa[100010];

	scanf("%s",s);
	const int n=strlen((char *)(s));

	SA_IS(s,sa,n+1,255,sizeof(unsigned char));

	rep(i,1,n+1) cout << sa[i] << endl;
	return 0;
}