using C = complex<R>;
// いざという時は複素数の掛け算を自分で定義する
void fft(vector<C> &a, bool inv) {
	const int n = a.size();
	const R sign = (inv ? -1.0 : 1.0);

	int rj = 0;
	rep(j, 1, n - 1) {
		for (int k = n >> 1; k > (rj ^= k); k >>= 1);
		if (j < rj) swap(a[j], a[rj]);
	}

	for (int m = 1; m < n; m <<= 1) {
		C wn = exp(C(0.0, sign * pi / m)), w = 1.0;
		rep(p, m) {
			for (int s = p; s < n; s += 2 * m) {
				C u = a[s], v = a[s + m] * w;
				a[s] = u + v, a[s + m] = u - v;
			}
			w *= wn;
		}
	}
	if (inv) rep(i, n) a[i] /= n;
}

vector<C> convolution(vector<C> a, vector<C> b) {
	int fft_size = 1;
	while (fft_size < a.size() + b.size()) fft_size <<= 1;

	a.resize(fft_size), fft(a, 0);
	b.resize(fft_size), fft(b, 0);

	vector<C> c(fft_size, 0.0);
	rep(i, fft_size) c[i] = a[i] * b[i];

	fft(c, 1);
	return c;
}