VP normalize_polygon(VP pol) {
	rep(i, pol.size()) {
		if (ccw(pol[(i + n - 1) % n], pol[i], pol[(i + 1) % n]) == ON)
			pol.erase(begin(pol) + i--);
	}
	return pol;
}

L bisector(P a, P b) {
	const P mid = (a + b) / P(2, 0);
	return L{mid, mid + (b - a)*P(0, 1)};
}

VP voronoi_cell(VP pol, VP v, int s) {
	rep(i, v.size()) {
		if (i == s) continue;
		pol = convex_cut(pol, bisector(v[s], v[i]));
	}
	return pol;
}
