// Description: 併合可能な順位キュー
// TimeComplexity: push,pop,meld $\mathcal{O}(\log N)$
// Verifyed: AOJ 2559

using T = ll;
struct Node {
	Node *l = nullptr, *r = nullptr;
	int rnk = 0, id;
	T val;
	Node() {}
	Node(T v, int id): val(v), id(id) {}
};

// memory pool
int total = 0;
Node pool[nmax];

Node* create(T v, int id) {
	pool[total] = Node(v, id);
	return &(pool[total++]);
}

Node* meld(Node* a, Node* b) {
	if (a == nullptr) return b;
	if (b == nullptr) return a;
	if (a->val > b->val) swap(a, b);
	a->r = meld(a->r, b);
	if (a->l == nullptr || a->l->rnk < a->r->rnk) swap(a->l, a->r);
	a->rnk = ((a->r == nullptr) ? 0 : a->r->rnk) + 1;
	return a;
}

Node* push(Node* x, int id) {return meld(x, create(w[id], id));}
Node* pop(Node* x) {return meld(x->l, x->r);}