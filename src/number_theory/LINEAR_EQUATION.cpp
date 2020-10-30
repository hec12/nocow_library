inline int pivoting(mat &a, int k, int &c) {
	int n = a.size(), m = a[0].size(), p = k, ret = 0;
	for (; c < m; ++c) {
		R cmax = abs(a[k][c]);
		rep(i, k + 1, n) if (chmax(cmax, abs(a[i][c]))) p = i, ret = 1;
		if (cmax > eps) break;
	}
	if (k != p) swap(a[k], a[p]);
	return ret;
}

int forward(mat &a) {
	int n = a.size(), m = a[0].size(), ret = 0, c = 0;
	rep(i, n - 1) {
		ret += pivoting(a, i, c);
		if (abs(a[i][c]) < eps) break;
		rep(j, i + 1, n) {
			R coef = 1.0 * a[j][c] / a[i][c];
			rep(k, c, m) a[j][k] -= 1.0 * coef * a[i][k];
		}
	}
	return ret;
}

int rank(mat &a) {
	int n = a.size(), m = a[0].size(), ret = 0;
	rep(i, n)rep(j, m) if (abs(a[i][j]) > eps) ret = i + 1;
	return ret;
}

double det(mat &a, int sgn) {
	R ret = 1.0;
	int n = a.size(), m = a[0].size();
	rep(i, n) ret *= a[i][i];
	if (sgn & 1) ret *= -1.0;
	return ret;
}

//backward substitution

vec back(mat &a) {
	int n = a.size(), m = a[0].size();
	vec x(0.0, n);
	for (int i = n - 1; i >= 0; i--) {
		R sum = 0.0;
		if (i + 1 < n) rep(j, i + 1, n) sum += 1.0 * a[i][j] * x[j];
		x[i] = 1.0 * (a[i][m - 1] - sum) / a[i][i];
	}
	return x;
}

int answer(mat &a) {
	int n = a.size(), m = a[0].size();
	int arank = 0, brank = 0;
	rep(i, n)rep(j, m - 1) if (abs(a[i][j]) > eps) arank = i + 1;
	rep(i, n)rep(j, m) if (abs(a[i][j]) > eps) brank = i + 1;
	if (arank != brank) return 0;
	if (arank < n) return 2;
	return 1;
}

vec gauss_jordan(mat &a) {
	const int n = a.size(), m = a[0].size();
	rep(i, n) {
		int pivot = i;
		rep(j, i, n) if (abs(a[j][i]) > abs(a[pivot][i])) pivot = j;
		swap(a[i], a[pivot]);

		if (abs(a[i][i]) < eps) return vec();

		rep(j, i + 1, m) a[i][j] /= a[i][i];
		rep(j, n) if (i != j) rep(k, i + 1, m) a[j][k] -= a[j][i] * a[i][k];
	}

	vec x(0.0, n);
	rep(i, n) x[i] = a[i][n];
	return x;
}