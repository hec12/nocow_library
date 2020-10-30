class Trie {
	Trie(int n, int m) {mov = vector<vector<int>>(n, vector<int>(m, -1)), nxt = 1;}
	void reset() {fill(_all(mov), -1), nxt = 1;}
	int query(const string &s) {
		int cur = 0;
		for (auto &c : s) {
			int idx = c - 'a';
			if (mov[cur][idx] == -1)
				cur = mov[cur][idx] = nxt++;
			else
				cur = mov[cur][idx];
		}
		return cur;
	}
private:
	vector<vector<int>> mov;
	int nxt;
};