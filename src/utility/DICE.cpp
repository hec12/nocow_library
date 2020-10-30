// Description: 六面体サイコロ
// Verifyed: Many Diffrent Problem

struct Dice {
	int l, r, f, b, d, u;
	Dice(int l, int r, int f, int b, int u, int d): l(l), r(r), f(f), b(b), u(u), d(d) {}

#define rotation(a,b,c,d) swap(a,b),swap(b,c),swap(c,d);

	void rot_f() { rotation(f, u, b, d);}
	void rot_b() { rotation(b, u, f, d);}
	void rot_l() { rotation(l, u, r, d);}
	void rot_r() { rotation(r, u, l, d);}
};
