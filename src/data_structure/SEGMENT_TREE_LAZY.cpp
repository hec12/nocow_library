class Segment_tree{

	using T=int; using U=int;
	int n,h;
	vector<T> data; vector<U> lazy;
	const T out_t=0; const U out_u=0;

	Segment_tree(int m){n=m,h=32-__builtin_clz(n),data.assign(2*n,out),lazy.assign(n,out);}

	// data merge
	T vmerge(T l,T r){ return min(l,r);}

	// calculate data value
	void calc(int p, int k) {
		if (lazy[p] == out_u) 
			data[p] = vmerge(data[p<<1],data[p<<1|1]);
		else 
			data[p] = lazy[p] * k;
	}

	// lazy_evaluation
	void apply(int p, U v){
		data[p]+=v;
		if(p < n) lazy[p] += v;
	}

	void build(int l, int r) {
		int k = 2;
		for (l += n, r += n-1; l > 1; k <<= 1) {
			l >>= 1, r >>= 1;
			for (int i = r; i >= l; --i) calc(i, k);
		}
	}

	void push(int p){
		for(int s = h; s > 0; --s) {
			int i = p >> s;
			if(lazy[i] != out_u){
				apply(i<<1,  lazy[i]),apply(i<<1|1,lazy[i]);
				lazy[i] = out_u;
			}
		}
	}

	void update(int l, int r, int v){
		l += n, r += n;
		int l0 = l, r0 = r;
		for (; l < r; l >>= 1, r >>= 1) {
			if(l&1) apply(l++, v);
			if(r&1) apply(--r, v);
		}
		build(l0, l0 + 1),build(r0 - 1, r0);
	}

	T query(int l, int r) {
		l += n, r += n;
		push(l),push(r-1);
		T resl =out_t,resr=out_t;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l&1) resl = vmerge(t[l++],resl);
			if (r&1) resr = vmerge(resr,t[--r]);
		}
		return vmerge(resl,resr);
	}
};