// Description: (d+1)個の点からd次式を補間
// TimeComplexity: $\mathcal{O}(N^2)$
// Verifyed: AOJ 1328

R Lagrange_interpolation(vector<R> xi, vector<R> fi, R x) {
	const int n = xi.size();
	R f = 0.0;
	rep(i, n) {
		R li = 1.0;
		rep(j, n) {
			if (i == j) continue;
			li *= (x - xi[j]) / (xi[i] - xi[j]);
		}
		f += fi[i] * li;
	}
	return f;
}