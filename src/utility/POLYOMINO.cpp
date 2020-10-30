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
