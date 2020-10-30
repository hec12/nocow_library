#define is_lms(i) (i>0 && t[i] && !t[i-1])

void get_buckets(auto &s,auto &bkt,int n, int K, bool end=true) {
    int sum=0;
    fill(bkt,bkt+K+1,0);
    rep(i,n) bkt[s[i]]++; 
    rep(i,K+1) sum+=bkt[i],bkt[i]=(end?sum:sum-bkt[i]);
}

void induce_sal(auto &t,auto &sa, auto &s,auto &bkt,int n,int K) {
    getBuckets(s,bkt,n,K,false);
    rep(i,n){
        int j=sa[i]-1;
        if(j>=0 && !t[j]) sa[bkt[s[j]]++]=j;
    }
}

void induce_sas(auto &t,auto &sa,auto &s,int *bkt,int n,int K){
    getBuckets(s,bkt,n,K,cs,true); 
    rrep(i,n){
        int j=sa[i]-1;
        if(j>=0 && t[j]) sa[--bkt[s[j]]]=j;
    }
}

void rec(auto &s,auto &sa,int n,int K) {
    vector<bool> t(n,false);
    
    t[n-1]=1,t[n-2]=0;
    rrep(i,n-2) t[i]=(s[i]<s[i+1] || (s[i]==s[i+1] && t[i+1]==1));

    vector<int> btk(K+1);
    getBuckets(s,bkt,n,K);

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

    auto &sa1=sa,&s1=sa+n-n1;
    
    if(name<n1) 
        rec(s1,sa1,n1,name-1);
    else
        rep(i,n1) sa1[s1[i]] = i;

    getBuckets(s,bkt,n,K);
    for(int i=1,j=0;i<n; i++) if(is_lms(i)) s1[j++]=i;

    rep(i,n1)  sa1[i]=s1[sa1[i]];
    fill(sa+n1,sa+n,-1);

    rrep(i,n1){
        int j=sa[i],sa[i]=-1;
        sa[--bkt[s[j]]]=j;
    }

    induce_sal(t,sa,s,bkt,n,K);
    induce_sas(t,sa,s,bkt,n,K);
}


auto sa_is(string str){
    const int n=str.size();
    vector<int> s(n+1,0),sa(n+1),rnk(n+1,0);
    rep(i,n) s[i]=str[i]-'a'+1;
    rec(s,sa,n+1,26);
    rep(i,n+1) rnk[sa[i]]=i;
    return make_tuple(rnk,sa);
}