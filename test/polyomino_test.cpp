#include <bits/stdc++.h>

#define _overload(_1,_2,_3,name,...) name
#define _rep(i,n) _range(i,0,n)
#define _range(i,a,b) for(int i=int(a);i<int(b);++i)
#define rep(...) _overload(__VA_ARGS__,_range,_rep,)(__VA_ARGS__)

#define _rrep(i,n) _rrange(i,n,0)
#define _rrange(i,a,b) for(int i=int(a)-1;i>=int(b);--i)
#define rrep(...) _overload(__VA_ARGS__,_rrange,_rrep,)(__VA_ARGS__)

#define _all(arg) begin(arg),end(arg)
#define uniq(arg) sort(_all(arg)),(arg).erase(unique(_all(arg)),end(arg))
#define getidx(ary,key) lower_bound(_all(ary),key)-begin(ary)
#define clr(a,b) memset((a),(b),sizeof(a))
#define bit(n) (1LL<<(n))
#define popcount(n) (__builtin_popcountll(n))

using namespace std;

template<class T>bool chmax(T &a, const T &b) { return (a < b) ? (a = b, 1) : 0;}
template<class T>bool chmin(T &a, const T &b) { return (b < a) ? (a = b, 1) : 0;}

using ll = long long;
using R = long double;
const R EPS = 1e-9L; // [-1000,1000]->EPS=1e-8 [-10000,10000]->EPS=1e-7
inline int sgn(const R& r) {return (r > EPS) - (r < -EPS);}
inline R sq(R x) {return sqrt(max(x, 0.0L));}

const int dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
const int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};

// Problem Specific Parameter:
#define fst first
#define snd second

using pii = pair<int, int>;
using Polyomino = vector<pii>;

const int limit = 10;
vector<Polyomino> polyomino[limit + 1];

void init() {
	polyomino[1].push_back({pii(0, 0)});

	for (int n = 2; n <= limit; ++n) {
		for (const auto &cur : polyomino[n - 1]) {
			rep(i, n - 1) rep(d, 4) {
				const int nx = cur[i].fst + dx[d];
				const int ny = cur[i].snd + dy[d];
				if (find(begin(cur), end(cur), pii(nx, ny)) != end(cur)) continue;

				Polyomino nxt = cur;
				nxt.push_back(pii(nx, ny));
				
				pii cmin = nxt[0];

				rep(j, n) {
					chmin(cmin.fst, nxt[j].fst);
					chmin(cmin.snd, nxt[j].snd);
				}

				rep(j, n) {
					nxt[j].fst -= cmin.fst;
					nxt[j].snd -= cmin.snd;
				}

				sort(begin(nxt), end(nxt));
				polyomino[n].push_back(nxt);

			}
		}

		sort(begin(polyomino[n]), end(polyomino[n]));
		polyomino[n].erase(unique(begin(polyomino[n]), end(polyomino[n])), end(polyomino[n]));
		cerr << n << " " << polyomino[n].size() << endl;
	}
	return ;
}

int main(void) {
	init();
	return 0;
}