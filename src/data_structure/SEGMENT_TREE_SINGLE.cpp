// http://codeforces.com/blog/entry/18051

class Segment_tree{
	using T=int;

    int n;
    vector<T> data;
    const T out=0;

    Segment_tree(int n){data.assign(2*n,out);}

	void update(int l, int r, int x) {
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l&1) data[l++]+= x;
			if (r&1) data[--r]+= x;
		}
	}

	int at(int p){
		int ret = 0;
		for (p += n; p > 0; p >>= 1) ret += data[p];
		return ret;
	}
};
