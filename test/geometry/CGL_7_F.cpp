int main(void){
    P p;
    C c;
    cin >> p >> c.c >> c.r;
    auto res=contact(c,p);
    cout.precision(20);
    for(auto &it:res) cout << fixed << real(it) << " " << imag(it) << endl;
    return 0;
}