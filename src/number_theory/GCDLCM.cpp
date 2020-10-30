// Description: 最大公約数と最小公倍数 
// TimeComplexity: $\mathcal{O}(\log n)$
// Verifyed: AOJ NTL_1_C

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;}