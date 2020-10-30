// verify yukicoder 0187
// http://www.csee.umbc.edu/~lomonaco/s08/441/handouts/Garner-Alg-Example.pdf
ll chinese_remainder(vector<ll> b,vector<ll> m){
	int n=m.size();
	set<ll> prime;
	rep(i,n){
		ll cur=m[i];
		for(ll f=2;f*f<=cur;++f){
			if(cur%f) continue;
			while(cur%f==0) cur/=f;
			prime.insert(f);
		}
		if(cur>1) prime.insert(cur);
	}

	vector<ll> factor(n);
	for(auto &p:prime){
		int index=0;
		rep(i,n){
			factor[i]=1LL;
			ll cur=m[i];
			while(cur%p==0) factor[i]*=p,cur/=p;
			if(factor[i]>factor[index]) index=i;
		}
		rep(i,n)if(i!=index){
			if(factor[i]==1) continue;
			if(b[index]%factor[i]!=b[i]%factor[i]) return -1;
			m[i]/=factor[i],b[i]%=m[i];
		}
	}

	vector<ll> constant(n,0LL),coef(n,1LL),v(n,0LL);
	rep(i,n){
		v[i]=SUB(b[i],constant[i],m[i]);
		v[i]=DIV(v[i],coef[i],m[i]);
		rep(j,i+1,n){
			constant[j]=ADD(constant[j],MUL(v[i],coef[j],m[j]),m[j]);
			coef[j]=MUL(coef[j],m[i],m[j]);
		}
	}

	ll ans=0LL;
	rrep(i,n) ans=ADD(MUL(ans,m[i],mod),v[i],mod);
	return ans;
}