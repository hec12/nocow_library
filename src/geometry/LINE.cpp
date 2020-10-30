// vertical parallel
// verified: AOJ CGL_2_A
bool vertical(L a, L b) {return sdot(0, vec(a), vec(b)) == 0;}
bool parallel(L a, L b) {return sdet(0, vec(a), vec(b)) == 0;}
bool eql(L a, L b) { return parallel(a, b) and sdet(a.s, a.t, b.s) == 0;}

// crossing determination
// verified: AOJ CGL_2_B
bool iss(L a, L b) {
	int sa = sdet(a.s, a.t, b.s) * sdet(a.s, a.t, b.t);
	int sb = sdet(b.s, b.t, a.s) * sdet(b.s, b.t, a.t);
	return max(sa, sb) < 0;
}

// crossing point
// verified: AOJ CGL_2_C
P cross(L a, L b) {
	R u = det(a.s, b.s, b.t) / det(0, vec(a), vec(b));
	return (1 - u) * a.s + u * a.t;
}

// distance
// verified: AOJ CGL_2_D
R dsp(L l, P p) {
	P h = proj(l, p);
	if (sdot(l.s, l.t, p) <= 0) h = l.s;
	if (sdot(l.t, l.s, p) <= 0) h = l.t;
	return abs(p - h);
}

R dss(L a, L b) {
	if(iss(a,b)) return 0;
	return min({dsp(a, b.s), dsp(a, b.t), dsp(b, a.s), dsp(b, a.t)});
}
