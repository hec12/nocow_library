// farthest point pair Verify AOJ CGL_4_B
R fpp(VP pol) {
	int n = pol.size(), i = 0, j = 0;
	if (n <= 2) return abs(pol[0] - pol[1]);
	R res = 0.0;

	auto cmp_x = [](P a, P b)->bool{
		int sr = sgn(real(a - b)), si = sgn(imag(a - b));
		return sr ? sr < 0 : si < 0;
	};

	rep(k, n) {
		if (!cmp_x(pol[i], pol[k]))i = k;
		if (cmp_x(pol[j], pol[k]))j = k;
	}

	int si = i, sj = j;
	while (i != sj || j != si) {
		res = max(res, abs(pol[i] - pol[j]));
		P li = vec(L{at(pol, i), at(pol, i + 1)});
		P lj = vec(L{at(pol, j), at(pol, j + 1)});
		if (sdet(0, li, lj) < 0)
			i = (i + 1) % n;
		else
			j = (j + 1) % n;
	}
	return res;
}
