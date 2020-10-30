// Description: 動的ConvexHullTrick
// TimeComplexity: $\mathcal{O}(\log V) per a query$
// Verifyed: CS_ACADEMY 70 E
// Compare: min -> less  max->greater
template <typename T,int memory_size,class Compare, T left,T right> class DynamicConvexHullTrick{
private:
	struct Node {
		Node *lch,*rch;
		T a,b;
		Node(){}
		Node(T a,T b){
			this->a = a;
			this->b = b;
			lch = rch = nullptr;
		}

		T getval(T x){
			return a * x + b;
		}

		void swap_line(Node *tar){
			swap(a,tar->a);
			swap(b,tar->b);
		}
	};

	// memory pool
	int total = 0;
	array<Node,memory_size> pool;

	Node* create(Node* tar) {
		pool[total] = *tar;
		return &(pool[total++]);
	}

	Node* root;

	void insert(Node* &cur, Node* tar, T l,T r){
		const T m = (l + r) / 2;

		if(cur == nullptr){
			cur = create(tar);
			return;
		}

		const bool cl = Compare()(cur->getval(l), tar->getval(l));
		const bool cr = Compare()(cur->getval(r), tar->getval(r));

		if (cl == true and cr == true) return;
		if (cl == false and cr == false) return cur->swap_line(tar);
		if (cl == false) cur->swap_line(tar);

		const bool cm = Compare()(cur->getval(m), tar->getval(m));

		if (cm) {
			insert(cur->rch, tar, m, r);
		} else {
			cur->swap_line(tar);
			insert(cur->lch, tar, l, m);
		}
	}

	T query(Node* cur,T x,T l,T r){
		const T m = (l + r) / 2;
		T ret = cur->getval(x);
		
		if (x < m) {
			if(cur->lch != nullptr) {
				T val = query(cur->lch,x,l,m);
				if(Compare()(ret,val) == false) {
					ret = val;
				}
			}
		} else {
			if(cur->rch != nullptr) {
				T val = query(cur->rch,x,m,r);
				if(Compare()(ret,val) == false){
					ret = val;
				}
			}
		}

		return ret;
	}

	void traversal(Node* &cur,T l,T r){
		const T m = (l + r) / 2;
		cerr << cur->a << " " << cur->b << " " << l << " " << r << endl;
		if(cur->lch != nullptr) traversal(cur->lch, l,m);
		if(cur->rch != nullptr) traversal(cur->rch, m,r);
	}
	
	public:
		void insert(T a, T b) {
			Node tar = Node(a,b);
			insert(root,&tar,left,right);
		}

		T query(T x) {
			return query(root,x,left,right);
		}

		void traversal(){
			if(root != nullptr) traversal(root,left,right);
		}
};
