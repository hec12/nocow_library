template<unsigned MOD>  class ModInt {
public:
	ModInt(): x(0) {}
	ModInt(signed y) : x(y >= 0 ? y % MOD : MOD - (-y) % MOD) {}
	ModInt(signed long long y) : x(y >= 0 ? y % MOD : MOD - (-y) % MOD) {}


	// Arithmetic Oprators
	ModInt &operator+=(ModInt that) {
		if ((x += that.x) >= MOD) x -= MOD; 
		return *this;
	}
	ModInt &operator-=(ModInt that) {
		if ((x += MOD - that.x) >= MOD) x -= MOD; 
		return *this;
	}
	ModInt &operator*=(ModInt that) {
		x = 1LL * x * that.x % MOD;
		return *this;
	}
	ModInt &operator/=(ModInt that) {
		return *this *= ModInt(get<1>(extgcd(that.x, int(MOD))));
	}
	ModInt &operator%=(ModInt that) {
		x %= that.x;
		return *this;
	}

	ModInt &operator+=(const int that) { return *this += ModInt(that);}
	ModInt &operator-=(const int that) { return *this -= ModInt(that);}
	ModInt &operator*=(const int that) { return *this *= ModInt(that);}
	ModInt &operator/=(const int that) { return *this /= ModInt(that);}
	ModInt &operator%=(const int that) { return *this %= ModInt(that);}

	// Comparators
	bool operator <(ModInt that) { return x < that.x; }
	bool operator >(ModInt that) { return x > that.x; }
	bool operator<=(ModInt that) { return x <= that.x; }
	bool operator>=(ModInt that) { return x >= that.x; }
	bool operator!=(ModInt that) { return x != that.x; }
	bool operator==(ModInt that) { return x == that.x; }

	// Utilities
	unsigned getval() const { return x;}
	ModInt operator+(ModInt that) const { return ModInt(*this) += that;}
	ModInt operator-(ModInt that) const { return ModInt(*this) -= that;}
	ModInt operator*(ModInt that) const { return ModInt(*this) *= that;}
	ModInt operator/(ModInt that) const { return ModInt(*this) /= that;}
	ModInt operator%(ModInt that) const { return ModInt(*this) %= that;}
	ModInt operator+(const int that) const { return ModInt(*this) += that;}
	ModInt operator-(const int that) const { return ModInt(*this) -= that;}
	ModInt operator*(const int that) const { return ModInt(*this) *= that;}
	ModInt operator/(const int that) const { return ModInt(*this) /= that;}
	ModInt operator%(const int that) const { return ModInt(*this) %= that;}
	ModInt operator=(const int that) { return *this = ModInt(that);}
	friend istream &operator>>(istream& is, ModInt &that) {ll tmp; is >> tmp; that = ModInt(tmp);return is;}
	friend ostream &operator<<(ostream& os, const ModInt &that) { return os << that.x; }
	
	ModInt power(ll n) const {
		ll b = 1LL, a = x;
		while(n){
			if(n & 1) b = b * a % MOD;
			a = a * a % MOD;
			n >>= 1;
		}
		return ModInt(b);
	}
private:
	unsigned x;
	
	inline auto extgcd(int a, int b) {
		if (b == 0) return make_tuple(a, 1, 0);
		tuple<int, int, int> ret = extgcd(b, a % b);
		swap(get<1>(ret), get<2>(ret));
		get<2>(ret) -= a / b * get<1>(ret);
		return ret;
	}
};

const int mod = 1000000007;
using mint = ModInt<mod>;
const mint ZERO = mint(0);
const mint ONE = mint(1);


vector<mint> Fact, InvFact;
void makeFact(int n){
	Fact = vector<mint>(n+1);
	Fact[0] = mint(1);
	rep(i,1,n+1) Fact[i] = mint(i) * Fact[i-1];

	InvFact = vector<mint>(n+1);
	InvFact[n] = mint(1) / Fact[n];
	rrep(i,n) InvFact[i] = mint(i+1) * InvFact[i+1];
}

mint Factorial(int n){ return Fact[n];}
mint InverseFactorial(int n){ return InvFact[n];}
mint Permutation(int n,int k){ return (n < 0 or k < 0 or n - k < 0) ? ZERO : Fact[n] * InvFact[n - k];}
mint Combination(int n,int k){ return (n < 0 or k < 0 or n - k < 0) ? ZERO : Fact[n] * InvFact[k] * InvFact[n-k];}
