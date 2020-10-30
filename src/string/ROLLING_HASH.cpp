// Mod candiate 1000000007,1000000009,1000000021,1000000033,1000000087,1000000093,1000000097

uniform_int_distribution<int> rng(1 << 20,mod - 1); // [lower,upper] 
mt19937 mt(pid);
const mint B = rng(mt);

const int limit = 200010;
mint hash[limit]

void init(const string &s){
	const int n = s.size();
	mint coef = 1;
	rep(i, n){
		const int val = (s[i] - 'a');
		if(i-1>=0) shash[i] = shash[i - 1];
		shash[i][j] += coef * val;
		coef *= B;
	}
}

mint calc(int l, int r) {
	mint ret = hash[r - 1];
	if (l - 1 >= 0) ret -= hash[l - 1];
	ret /= B.power(l);
	return ret;
}
