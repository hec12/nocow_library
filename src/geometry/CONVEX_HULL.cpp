// convex_hull Verify AOJ CGL_4_A
VP convex_hull(VP pol) {
	int n = pol.size(), k = 0, t = 1;

	auto cmp_x = [](P a, P b)->bool{
		int sr = sgn(real(a - b)), si = sgn(imag(a - b));
		return sr ? sr < 0 : si < 0;
	};

	sort(begin(pol), end(pol), cmp_x);
	VP res(2 * n);

	auto push = [&](P p)->void{
		while (k > t and sdet(res[k - 1], res[k - 2], p) >= 1) k--;
		res[k++] = p;
	};

	for_each(begin(pol), end(pol), push);
	t = k;
	for_each(rbegin(pol) + 1, rend(pol), push);
	res.resize(k - 1);
	return res;
}