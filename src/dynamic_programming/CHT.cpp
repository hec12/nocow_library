// Description: DP using Convex hull Trick
// TimeComplexity: $ \mathcal{O}(n)$
// Verifyed: AOJ 2725

//Inequality sign min >=  max <=
template<typename T> class CHT {
public:
	T getval(T x) {
		while (deq.size() >= 2 && f(deq[0], x) <= f(deq[1], x)) deq.pop_front();
		return f(deq[0], x);
	}

	void push(T ca, T cb) {
		const int idx = a.size();
		a.push_back(ca), b.push_back(cb);
		while (deq.size() >= 2 && check(idx)) deq.pop_back();
		deq.push_back(idx);
	}

	int size() {return deq.size();}
private:
	vector<T> a, b;
	deque<int> deq;

	T f(int idx, T x) {return 1LL * a[idx] * x + b[idx];}

	bool check(int idx) {
		const int i = deq[size() - 2], j = deq[size() - 1], k = idx;
		return (b[j] - b[i]) * (a[k] - a[j]) <= (b[k] - b[j]) * (a[j] - a[i]);
	}
};