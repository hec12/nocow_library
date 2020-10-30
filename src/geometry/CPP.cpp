// closest point pair Verify AOJ CGL_5_A
R cpp(VP a, int flag = 1) {
	const int n = a.size(), m = n / 2;
	if (n <= 1) return INF;

	auto cmp_x = [](P a, P b)->bool{
		int sr = sgn(real(a - b)), si = sgn(imag(a - b));
		return sr ? sr < 0 : si < 0;
	};

	if (flag) sort(begin(a), end(a), cmp_x);

	VP b(begin(a), begin(a) + m), c(begin(a) + m, end(a));
	R x = real(a[m]), d = min(cpp(b, 0), cpp(c, 0));


	auto cmp_y = [](P a, P b)->bool{
		int sr = sgn(real(a - b)), si = sgn(imag(a - b));
		return si ? si < 0 : sr < 0;
	};

	sort(begin(a), end(a), cmp_y);
	deque<P> e;

	for (auto &p : a) {
		if (abs(real(p) - x) >= d) continue;

		for (auto &q : e) {
			if (imag(p - q) >= d) break;
			d = min(d, abs(p - q));
		}
		e.push_front(p);
	}
	return d;
}
