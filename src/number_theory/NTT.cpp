// $2^{23}$ より大きく，primitive rootに3を持つもの
// const ll mods[] = { 1224736769, 469762049, 167772161,
// 595591169, 645922817, 897581057, 998244353 };
// $1.5*10^5*10^{4} = 150000*100$
// $5*2^{23}+1 = 998244353$

void ntt(vector<mint> &a, bool inv) {
	const int n = a.size();

	mint base = mint(3).power((mod - 1) / n);
	if (inv) base = ONE / base;

	int rj = 0;
	rep(j, 1, n - 1) {
		for (int k = n >> 1; k > (rj ^= k); k >>= 1);
		if (j < rj) swap(a[j], a[rj]);
	}

	for (int m = 1; m < n; m <<= 1) {
		const mint wn = base.power(n / 2 / m);
		mint w = ONE;

		rep(p, m) {
			for (int s = p; s < n; s += 2 * m) {
				mint u = a[s], v = a[s + m] *  w;
				a[s] = u + v, a[s + m] = u - v;
			}
			w *= wn;
		}
	}

	const mint n_inv = ONE / mint(n);
	if (inv) rep(i, n) a[i] *= n_inv;
}

vector<mint> convolution(vector<mint> a, vector<mint> b) {
	int ntt_size = 1;
	while (ntt_size < a.size() + b.size()) ntt_size <<= 1;

	a.resize(ntt_size), ntt(a, 0);
	b.resize(ntt_size), ntt(b, 0);

	vector<mint> c(ntt_size, ZERO);
	rep(i, ntt_size) c[i] = a[i] * b[i];

	ntt(c, 1);
	return c;
}