// Circle // verified: AOJ 1183
enum RCC {OUT = 2, ON_OUT = 1, ISC = 0, ON_IN = -1, IN = -2};
int rcc(C a, C b) { 
	R d = abs(a.c - b.c); 
	return sgn(d - a.r - b.r) + sgn(d - abs(a.r - b.r));
}

// circle crossing determination
bool icp(C c, P p, int end = 0) {return sgn(abs(p - c.c) - c.r) <= -end;}
bool ics(C c, L s, int end = 0) {
	if (sgn(dsp(s, c.c) - c.r) > end) return false;
	if (icp(c, s.s, end) and icp(c, s.t, end)) return false;
	return true;
}
// common area between circles
R area(C a, C b) {
	int r = rcc(a, b);
	if (r >= ON_OUT) return 0.0L;
	if (r <= ON_IN) return min(norm(a.r), norm(b.r)) * PI;
	R d = abs(b.c - a.c), rc = (norm(d) + norm(a.r) - norm(b.r)) / (2.0 * d);
	R t = acos(rc / a.r), p = acos((d - rc) / b.r);
	return norm(a.r) * t + norm(b.r) * p - d * a.r * sin(t);
}

// cross point between circle and line
// verified: AOJ CGL_7_D
P cir(C c, R t) {return c.c + polar(c.r, t);}
VP cross(C c, L l) {
	P h = proj(l, c.c);
	P e = polar(sq(norm(c.r) - norm(h - c.c)), arg(vec(l)));
	return VP{h - e, h + e};
}

// cross point between circles
// verified: AOJ CGL_7_E
VP cross(C a, C b) {
	P d = b.c - a.c;
	P w = (norm(d) + norm(a.r) - norm(b.r)) / (2.0L * norm(d)) * d;
	return cross(a, {a.c + w, a.c + w + 1il * d});
}

// circle tangent
// verified: AOJ CGL_7_F
L tan(C c, P p) {return L{p, p + 1il * (p - c.c)};}

P helper(C c, P d, R r, P j) {
	P tmp = sq(norm(d) - norm(r)) * j;
	P dir = (r + tmp) / norm(d) * d;
	return c.c + c.r * dir;
}

VP contact(C c, P p) {
	VP ret;
	P d = p - c.c;
	for (P j : { -1il, 1il}) ret.emplace_back(helper(c, d, c.r, j));
	sort(begin(ret), end(ret));
	ret.erase(unique(begin(ret), end(ret)), end(ret));
	return ret;
}

// circle tangent
// Verified: AOJ CGL_7_G
VP contact(C a, C b) {
	VP ret;
	P d = b.c - a.c;
	for (int s : { -1, 1}) {
		if (rcc(a, b) >= s) {
			for (P j : { -1i, 1i}) {
				R r = a.r + s * b.r;
				ret.emplace_back(helper(a, d, r, j));
			}
		}
	}
	sort(begin(ret), end(ret));
	ret.erase(unique(begin(ret), end(ret)), end(ret));
	return ret;
}

// common area of circle and polygon
// verified: AOJ CGL_7_H
R area_helper(C c, P a, P b) {
	if (icp(c, a) and icp(c, b)) return det(0, a, b) / 2.0l;
	return norm(c.r) * arg(conj(a) * b) / 2.0l;
}

R area(C c, P a, P b) {
	L l = {a, b};

	if (sgn(min({c.r, abs(a), abs(b), abs(b - a)})) == 0) return 0.0;
	if (ics(c, l) == false) return area_helper(c, a, b);

	R res = 0.0; VP ary;
	ary.push_back(a);
	for (auto &p : cross(c, l)) if (sdot(p, a, b) < 0) ary.push_back(p);
	ary.push_back(b);

	rep(i, ary.size() - 1) res += area_helper(c, at(ary, i), at(ary, i + 1));
	return res;
}

R area(C c, VP pol) {
	R res = 0;
	rep(i, pol.size()) {
		P a = at(pol, i) - c.c , b = at(pol, i + 1) - c.c;
		res += area(C{0.0L, c.r}, a, b);
	}
	return res;
}
