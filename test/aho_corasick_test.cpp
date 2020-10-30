#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;(i)<(n);++(i))
using namespace std;

template<class T>bool chmax(T &a, const T &b) { return (a < b) ? (a = b, 1) : 0;}
template<class T>bool chmin(T &a, const T &b) { return (b < a) ? (a = b, 1) : 0;}

// Description: 複数文字列パターンマッチングオートマトン
// TimeComplexity: $\mathcal{O}(\sum{|S|})$
// Verifyed: Todo

const int sigma = 26;
inline int convert(char& arg) {
	// 1-indexed
	return arg - 'a' + 1;
}

vector<vector<int>> fg; // 0 faliure otherwise goto
vector<vector<int>> ac;

auto set_union(const vector<int> &a, const vector<int> &b) {
	vector<int> res;
	set_union(begin(a), end(a), begin(b), end(b), back_inserter(res));
	return res;
}

void add_state() {
	fg.push_back(vector<int>(1 + sigma, 0));
	ac.push_back(vector<int>());
}

int build(vector<string> &pattern) {
	fg.clear();
	ac.clear();

	const int root = 1;
	rep(loop, 2) add_state();
	fg[root][0] = root; // root failure

	// Trie
	rep(i, pattern.size()) {
		int now = root;
		for (auto &c : pattern[i]) {
			int j = convert(c);

			if (fg[now][j] == 0) {
				fg[now][j] = int(fg.size());
				add_state();
			}
			now = fg[now][j];
		}
		ac[now].push_back(i);
	}

	// Aho-corasick
	queue<int> q;
	for (int i = 1; i <= sigma; ++i) {
		if (fg[root][i]) {
			fg[fg[root][i]][0] = root;
			int nxt = fg[root][i];
			q.push(nxt);
		} else
			fg[root][i] = root;
	}

	// abcと遷移した時にbcも検知できるようにしている.
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (int i = 1; i <= sigma; ++i) {
			if (fg[now][i]) {
				int nxt = fg[now][0];
				while (!fg[nxt][i]) nxt = fg[nxt][0];
				fg[fg[now][i]][0] = fg[nxt][i];
				ac[fg[now][i]] = set_union(ac[fg[now][i]], ac[fg[nxt][i]]);
				q.push(fg[now][i]);
			}
		}
	}
	return root;
}

vector<int> match(int root, string &s, vector<string> &pattern) {
	int now = root;
	vector<int> res(pattern.size(), 0);
	for (auto &c : s) {
		int i = convert(c);
		while (!fg[now][i]) now = fg[now][0];
		now = fg[now][i];
		for (auto &j : ac[now]) res[j]++;
	}
	return res;
}

int main(void) {
	return 0;
}