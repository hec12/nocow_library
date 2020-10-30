int main(void){
	int n;
	cin >> n;
	VP pol;
	rep(i,n){
		P p;
		cin >> p;
		pol.push_back(p);
	}
	cout.precision(10);
	cout << fixed << fpp(pol) << endl;
	return 0;
}
