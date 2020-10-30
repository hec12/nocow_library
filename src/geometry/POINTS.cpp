//reflection verify AOJ CGL_1_B
P refl(L l, P p) {return 2.0L * proj(l, p) - p;}

// CCW verify AOJ CGL_1_C
enum CCW { LEFT = 1, RIGHT = 2, BACK = 4, FRONT = 8, ON = 16};
inline int ccw(P o, P a, P b) {
	if (sdet(o, a, b) > 0) return LEFT; // counter clockwise
	if (sdet(o, a, b) < 0) return RIGHT; // clockwise
	if (sdot(o, a, b) < 0) return BACK; // b--base--a on line
	if (sgn(norm(a - o) - norm(b - o)) < 0) return FRONT; // base--a--b on line
	return ON; // base--b--a on line  semnet determination betwenn a and b
}
