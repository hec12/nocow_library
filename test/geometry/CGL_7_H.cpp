int main(void) {
	int n;
	R r;
	cin >> n >> r;
	C c = C{0.0L, r};
	VP pol(n);
	rep(i, n) cin >> pol[i];
	cout.precision(20);
	cout << fixed << area(c, pol) << endl;
	return 0;
}
