int main(void){
	C c1,c2;
	cin >> c1.c >> c1.r >> c2.c >> c2.r;
		
	VP res=cross(c1,c2);
	if(real(res[0])-real(res[1])>0) swap(res[0],res[1]);
	if(abs(real(res[0])-real(res[1]))<EPS and (imag(res[0])-imag(res[1])>0)) swap(res[0],res[1]);
	cout.precision(20);
	cout << fixed << res[0] << " " << res[1] << endl;
	return 0;
}