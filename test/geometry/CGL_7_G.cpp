int main(void){
	C c1,c2;
	cin >> c1.c >> c1.r >> c2.c >> c2.r;
	VP res=contact(c1,c2);
	cout.precision(20);
	for(auto &p:res) cout << fixed << p << endl;
	return 0;
}