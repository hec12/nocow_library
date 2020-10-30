// Description: ベクトル
// Verifyed: various problem
using namespace placeholders;
using R = long double;
const R EPS = 1e-9L; // [-1000,1000]->EPS=1e-8 [-10000,10000]->EPS=1e-7
inline int sgn(const R& r) {return (r > EPS) - (r < -EPS);}
inline R sq(R x) {return sqrt(max(x, 0.0L));}

const R INF = 1E40L;
const R PI = acos(-1.0L);
using P = complex<R>;
using L = struct {P s, t;};
using VP = vector<P>;
using C = struct {P c; R r;};

#define at(a,i) (a[(i + a.size()) % a.size()])

auto& operator >> (istream& is, P& p) { R x, y; is >> x >> y, p = P(x, y); return is;}
auto& operator << (ostream& os, P& p) { os << real(p) << " " << imag(p); return os;}

namespace std {
bool operator <  (const P& a, const P& b) { return sgn(real(a - b)) ? real(a - b) < 0 : sgn(imag(a - b)) < 0;}
bool operator == (const P& a, const P& b) { return sgn(real(a - b)) == 0 && sgn(imag(a - b)) == 0;}
}

inline R dot(P o, P a, P b) {return real(conj(a - o) * (b - o));}
inline R det(P o, P a, P b) {return imag(conj(a - o) * (b - o));}
inline P vec(L l) {return l.t - l.s;}
auto sdot = bind(sgn, bind(dot, _1, _2, _3));
auto sdet = bind(sgn, bind(det, _1, _2, _3));

//projection verify AOJ CGL_1_A
P proj(L l, P p) { R u = real((p - l.s) / vec(l)); return (1 - u) * l.s + u * l.t;}
