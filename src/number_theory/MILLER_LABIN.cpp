const int limit=1000001;
bool prime[limit];

void init(){
	rep(i,limit) prime[i]=true;
	prime[0]=prime[1]=false;
	for(ll i=2;i*i<=limit;++i){
		if(prime[i])
			for(ll j=i*i;j<=limit;j+=i)
				prime[j]=false;
	}
	return;
}

bool square(ll arg){
	ll left=1LL,right=1e9;
	while(right-left>1){
		ll mid=(left+right)/2LL;
		if(mid*mid<=arg)
			left=mid;
		else
			right=mid;
	}
	return left*left==arg;
}

ll multiple(ll a,ll b,ll mod){
    ll res=0LL;
    for(;b;a=ADD(a,a,mod),b>>=1) if(b&1) res=ADD(res,a,mod);
    return res;
}

ll power(ll a,ll n,ll mod){
	ll res=1LL;
	for(;n;a=multiple(a,a,mod),n>>=1)if(n&1) res=multiple(res,a,mod);
	return res;
}

bool isprime(ll n){
	if(n==1) return false;
	if(n%2==0) return (n==2);
	const int base[12]={2,3,5,7,11,13,17,19,23,29,31,37};
	ll s=__builtin_ctz(n-1),d=(n-1)>>s;
	rep(i,12){
		if(power(base[i],d,n)==1) continue;
		bool ok=false;
		rep(j,s) if(power(base[i],d<<j,n)==n-1) ok=true;
		if(ok==false) return false;
	}
	return true;
}