template<int MOD> 
struct ModInt {
	static const int Mod = MOD;
	unsigned x;
	ModInt(): x(0){}
	ModInt(signed sig) {
		int sigt = sig % MOD; if(sigt < 0) sigt += MOD; x = sigt; 
	}

	ModInt(signed long long sig) { 
		int sigt = sig % MOD; if(sigt < 0) sigt += MOD; x = sigt; 
	}

	int getval() const { 
		return int(x); 
	}

	inline int extgcd(int a,int b,int& x,int& y){
		x=1,y=0;
		int g=a;
		if(b!=0){
			g=extgcd(b,a%b,y,x);
			y-=a/b*x;
		}
		return g;
	}

	ModInt &operator+=(ModInt that) { 
		if((x += that.x) >= MOD) x -= MOD; return *this; 
	}

	ModInt &operator-=(ModInt that) { 
		if((x += MOD - that.x) >= MOD) x -= MOD; return *this; 
	}

	ModInt &operator*=(ModInt that) { 
		x = 1LL * x * that.x % MOD; return *this; 
	}

	ModInt &operator/=(ModInt that) {
		int y,d; extgcd(that.x,MOD,y,d); return x = 1LL * x * y % MOD; return *this;
	}

	ModInt operator+(ModInt that) const { 
		return ModInt(*this) += that; 
	}
	ModInt operator-(ModInt that) const { 
		return ModInt(*this) -= that; 
	}
	ModInt operator*(ModInt that) const { 
		return ModInt(*this) *= that; 
	}
	ModInt operator/(ModInt that) const { 
		return ModInt(*this) /= that; 
	}
};

using mint=ModInt<1000000007>;

inline mint power(mint a,ll n){
	mint b(1LL);
	while(n){
		if(n & 1)
	}
for(;n;a*=a,n>>=1;) if(n&1) b*=a;
	return b;
}

mint C[3010][3010];
void comb_table(int n){ rep(i,n+1) rep(j,i+1) C[i][j]=(j==0 or j==i)?1LL:C[i-1][j-1]+C[i-1][j];}

mint I[1000010];
void inv_table(int n){I[1]=1LL;rep(i,2,n+1) I[i]=I[mint::Mod%i]*(mint::Mod-mint::Mod/i);}

mint F[1000010],IF[1000010];
void fact_table(int n){F[0]=IF[0]=1LL; rep(i,1,n+1) F[i]=F[i-1]*i,IF[i]=IF[i-1]*I[i];}

inline mint comb(int n,int k){return F[n]*IF[k]*IF[n-k];}
