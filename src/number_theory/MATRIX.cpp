using vec = valarray<R>;
using mat = valarray<vec>;

mat mul(mat a, mat b) {
	int m = a.size();
	mat c(vec(0.0, m), m);
	rep(i, m)rep(j, m) rep(k, m) c[i][j] += a[i][k] * b[k][j];
	return c;
}

mat power(mat a, int n) {
	int m = a.size();
	mat b(vec(0.0, m), m);
	rep(i, m) b[i][i] = 1.0;
	while (n) {
		if (n & 1) b = mul(b, a);
		a = mul(a, a);
		n >>= 1;
	}
	return b;
}