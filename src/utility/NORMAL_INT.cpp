template  class NormalInt {
public:
	NormalInt(): x(0) {}
	NormalInt(signed y) : x(y >= 0 ? y % MOD : MOD - (-y) % MOD) {}
	NormalInt(signed long long y) : x(y >= 0 ? y % MOD : MOD - (-y) % MOD) {}


	// Arithmetic Oprators
	NormalInt &operator+=(NormalInt that) {
		x += that.x;
		return *this;
	}
	NormalInt &operator-=(NormalInt that) {
		x -= that.x;
		return *this;
	}
	NormalInt &operator*=(NormalInt that) {
		x *= that.x;
		return *this;
	}
	NormalInt &operator/=(NormalInt that) {
		x /= that.x;
		return *this;
	}
	NormalInt &operator%=(NormalInt that) {
		x %= that.x;
		return *this;
	}

	NormalInt &operator+=(const auto that) { return *this += NormalInt(that);}
	NormalInt &operator-=(const auto that) { return *this -= NormalInt(that);}
	NormalInt &operator*=(const auto that) { return *this *= NormalInt(that);}
	NormalInt &operator/=(const auto that) { return *this /= NormalInt(that);}
	NormalInt &operator%=(const auto that) { return *this %= NormalInt(that);}

	// Comparators
	bool operator <(NormalInt that) { return x < that.x; }
	bool operator >(NormalInt that) { return x > that.x; }
	bool operator<=(NormalInt that) { return x <= that.x; }
	bool operator>=(NormalInt that) { return x >= that.x; }
	bool operator!=(NormalInt that) { return x != that.x; }
	bool operator==(NormalInt that) { return x == that.x; }

	// Utilities
	unsigned getval() const { return x;}
	NormalInt operator+(NormalInt that) const { return NormalInt(*this) += that;}
	NormalInt operator-(NormalInt that) const { return NormalInt(*this) -= that;}
	NormalInt operator*(NormalInt that) const { return NormalInt(*this) *= that;}
	NormalInt operator/(NormalInt that) const { return NormalInt(*this) /= that;}
	NormalInt operator%(NormalInt that) const { return NormalInt(*this) %= that;}
	NormalInt operator+(const int that) const { return NormalInt(*this) += that;}
	NormalInt operator-(const int that) const { return NormalInt(*this) -= that;}
	NormalInt operator*(const int that) const { return NormalInt(*this) *= that;}
	NormalInt operator/(const int that) const { return NormalInt(*this) /= that;}
	NormalInt operator%(const int that) const { return NormalInt(*this) %= that;}
	NormalInt operator=(const int that) { return *this = NormalInt(that);}
	friend istream &operator>>(istream& is, NormalInt &that) {ll tmp; is >> tmp; that = NormalInt(tmp);return is;}
	friend ostream &operator<<(ostream& os, const NormalInt &that) { return os << that.x; }
	
	NormalInt power(ll n) const {
		ll b = 1LL, a = x;
		while(n){
			if(n & 1) b = b * a;
			a = a * a;
			n >>= 1;
		}
		return NormalInt(b);
	}
private:
	ll x;
};

const int mod = 1000000007;
using mint = NormalInt<mod>;
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
mint Permutation(int n,int k){ return (n < 0 or k < 0 or n - k < 0) ? ZERO : Fact[n] * InvFact[k];}
mint Combination(int n,int k){ return (n < 0 or k < 0 or n - k < 0) ? ZERO : Fact[n] * InvFact[k] * InvFact[n-k];}
