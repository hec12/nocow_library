// Polygon

// area
// verified: AOJ 1100 CGL_3_A
R area(const VP& pol) {
	R sum = 0.0;
	rep(i, pol.size()) sum += det(0, at(pol, i), at(pol, i + 1));
	return abs(sum / 2.0L);
}

// convex_polygon determination
// verified: CGL_3_B
bool is_convex(const VP& pol) {
	rep(i, pol.size()){
		if(sdet(at(pol, i), at(pol, i + 1), at(pol, i + 2)) < 0){
			return false;
		}
	}
	return true;
}

// polygon realation determination  in  2 on 1 out 0　(possible non-convex)
// verified: AOJ CGL_3-C
int in_polygon(const VP& pol, const P& p) {
	int res = 0;
	auto simag = [](const P & p) {return sgn(imag(p));};
	rep(i, pol.size()) {
		P a = at(pol, i), b = at(pol, i + 1);
		if (sdet(p, a, b) == 0 and sdot(p, a, b) <= 0) return 1;
		bool f = simag(p - a) >= 0, s = simag(p - b) < 0;
		if (simag(b - a)*sdet(a, b, p) == 1 and f == s) res += (2 * f - 1);
	}
	return res ? 2 : 0;
}

// polygon realation determination　(possible non-convex)
// verified: not AOJ 2514
bool in_polygon(const VP& pol, const L& l) {
	VP check = {l.s, l.t};
	rep(i, pol.size()) {
		L edge = {at(pol, i), at(pol, i + 1)};
		if (iss(l, edge)) check.emplace_back(cross(l, edge));
	}

	auto cmp_x = [](P a, P b)->bool{
		int sr = sgn(real(a - b)), si = sgn(imag(a - b));
		return sr ? sr < 0 : si < 0;
	};

	sort(begin(check), end(check), cmp_x);
	rep(i, check.size() - 1) {
		P m = (at(check, i) + at(check, i + 1)) / 2.0L;
		if (in_polygon(pol, m) == false) return false;
	}
	return true;
}

// convex_cut
// verified: AOJ CGL_4_C
VP convex_cut(const VP& pol, const L& l) {
	VP res;
	rep(i, pol.size()) {
		P a = at(pol, i), b = at(pol, i + 1);
		int da = sdet(l.s, l.t, a), db = sdet(l.s, l.t, b);
		if (da >= 0) res.emplace_back(a);
		if (da * db < 0) res.emplace_back(cross({a, b}, l));
	}
	return res;
}
