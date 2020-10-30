int main(void){
	int q;
	C c;
	cin >> c.c >> c.r;
		
	cin >> q;
	cout.precision(20);
	rep(i,q){
		P a,b;
		cin >> a >> b;
		L l={a,b};
		VP res=cross(c,l);
		if(sgn(real(res[0])-real(res[1])>0)) swap(res[0],res[1]);
		if(sgn(real(res[0])-real(res[1]))==0 and sgn(imag(res[0])-imag(res[1]))>0) swap(res[0],res[1]);
		cout << fixed << res[0] << " " << res[1] << endl;
	}
	return 0;
}