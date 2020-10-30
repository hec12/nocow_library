// Treap based on merge and split
// each operation
// set parameter
const int inf = 1 << 29;
const int nmax = 1000010;

mt19937 mt;
uniform_real_distribution<double> rnd(0.0, 1.0);

struct Node {
	int val, cnt, min, add, rev;
	Node *lch = nullptr, *rch = nullptr;
	double pri;
	Node() {}
	Node(int v): val(v), cnt(1), min(v), add(0), rev(0), pri(rnd(mt)) {}
};

// memory pool
int total = 0;
Node pool[nmax];

Node* create(int v) {
	pool[total] = Node(v);
	return &(pool[total++]);
}

// helper function
int val(Node* x) {assert(x != nullptr); return x->val + x->add;}
int cnt(Node* x) {return (x == nullptr) ? 0 : x->cnt;}
int min(Node* x) {return (x == nullptr) ? inf : x->min + x->add;}

Node* update(Node* x) {
	if (x == nullptr) return x;

	x->cnt = 1 + cnt(x->lch) + cnt(x->rch);
	x->min = min({val(x), min(x->lch), min(x->rch)});

	if (x->add) {
		x->val += x->add;
		if (x->lch != nullptr) x->lch->add += x->add;
		if (x->rch != nullptr) x->rch->add += x->add;
		x->add = 0;
	}

	if (x->rev) {
		swap(x->lch, x->rch);
		if (x->lch != nullptr) x->lch->rev ^= true;
		if (x->rch != nullptr) x->rch->rev ^= true;
		x->rev = false;
	}

	return x;
}

Node* merge(Node* l, Node* r) {
	l = update(l), r = update(r);
	if (l == nullptr) return r;
	if (r == nullptr) return l;

	if (l->pri > r->pri) {
		l->rch = merge(l->rch, r);
		return update(l);
	} else {
		r->lch = merge(l, r->lch);
		return update(r);
	}
}

tuple<Node*, Node*> split(Node* x, int k) { //[0,k) [k,n)
	x = update(x);
	if (x == nullptr) return make_tuple(nullptr, nullptr);

	Node *l, *r;
	if (k <= cnt(x->lch)) {
		tie(l, r) = split(x->lch, k);
		x->lch = r;
		return make_tuple(update(l), update(x));
	} else {
		tie(l, r) = split(x->rch, k - cnt(x->lch) - 1);
		x->rch = l;
		return make_tuple(update(x), update(r));
	}
}

Node* range_merge(Node* left, Node* tar, Node* right) {
	return merge(left, merge(tar, right));
}

tuple<Node*, Node*, Node*> range_split(Node* t, int l, int r) {
	Node *left, *tar, *right;
	tie(tar, right) = split(t, r);
	tie(left, tar) = split(tar, l);
	return make_tuple(left, tar, right);
}

void insert(Node* &t, int k, int v) {
	Node *left, *right, *tar = create(v);
	tie(left, right) = split(t, k);
	t = range_merge(left, tar, right);
}

void erase(Node* &t, int k) {
	Node *left, *tar, *right;
	tie(left, tar, right) = range_split(t, k, k + 1);
	t = merge(left, right);
}

void change(Node* &t, int k, int v) {
	erase(t, k);
	insert(t, k, v);
}

void add(Node* &t, int l, int r, int a) {
	Node *left, *tar, *right;
	tie(left, tar, right) = range_split(t, l, r);
	tar->add += a;
	t = range_merge(left, tar, right);
}

void rev(Node* &t, int l, int r) {
	Node *left, *tar, *right;
	tie(left, tar, right) = range_split(t, l, r);
	tar->rev ^= true;
	t = range_merge(left, tar, right);
}

void rot(Node* &t, int l, int r, int k) {
	Node *left, *tar, *right;
	tie(left, tar, right) = range_split(t, l, r);
	Node *tar_l, *tar_r;
	tie(tar_l, tar_r) = split(tar, cnt(tar) - k);
	tar = merge(tar_r, tar_l);
	t = range_merge(left, tar, right);
}

int min(Node* &t, int l, int r) {
	Node *left, *tar, *right;
	tie(left, tar, right) = range_split(t, l, r);
	int ret = tar->min;
	t = range_merge(left, tar, right);
	return ret;
}