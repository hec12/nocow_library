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

template<class T>bool chmax(T &a, const T &b) { return (a<b)?(a=b,1):0;}
template<class T>bool chmin(T &a, const T &b) { return (b<a)?(a=b,1):0;}

using ll=long long;
using R=long double;
const R EPS=1e-9; // [-1000,1000]->EPS=1e-8 [-10000,10000]->EPS=1e-7
inline int sgn(const R& r){return(r > EPS)-(r < -EPS);}
inline R sq(R x){return sqrt(max<R>(x,0.0));}

const int dx[8]={1,0,-1,0,1,-1,-1,1};
const int dy[8]={0,1,0,-1,1,1,-1,-1};

// Problem Specific Parameter:
const int nmax=200010;
int a[nmax],b[nmax];
ll w[nmax];
ll sum=0LL,ans[nmax];

// Description: グラフの型定義(これは最小費用流)
// Verifyed: Many Diffrent Problem 

//Appropriately Changed
using edge=struct{int to,id;};
using G=vector<vector<edge>>;

//Appropriately Changed
void add_edge(G &graph,int from,int to,int id){ 
	graph[from].push_back({to,id});
	graph[to].push_back({from,id});
}

// Description: 素集合を管理するデータ構造 
// TimeComplexity: 初期化$\mathcal{O}(n)$ 更新$\mathcal{O}(\log n)$
// Verifyed: AOJ DSL_1_A

class Union_find{
	public:
	    Union_find(int n){par.resize(n),iota(_all(par),0);}
	    void init(){iota(_all(par),0);}
	    int find(int x){return (par[x]==x)?x:par[x]=find(par[x]);}
	    void unite(int a,int b){a=find(a),b=find(b);par[a]=b;}
		bool same(int a,int b){return find(a)==find(b);}
	private:
		vector<int> par;
};

Union_find* uf;

// Description: 併合可能な順位キュー
// TimeComplexity: push,pop,meld $\mathcal{O}(\log N)$ 
// Verifyed: AOJ 2559 (todo)

using T=ll;
struct Node{
    Node *l=nullptr,*r=nullptr;
    int rnk=0,id;
    T val;
    Node(){}
    Node(T v,int id): val(v),id(id){}
};

// memory pool
int total=0;
Node pool[2*nmax];

Node* create(T v,int id){
    pool[total]=Node(v,id);
    return &(pool[total++]);    
}

Node* meld(Node* a,Node* b) {
    if(a==nullptr) return b;
    if(b==nullptr) return a;
    if(a->val > b->val) swap(a,b);
    a->r=meld(a->r,b);
    if(a->l == nullptr || a->l->rnk < a->r->rnk) swap(a->l,a->r);
    a->rnk=((a->r == nullptr)?0:a->r->rnk)+1;
    return a;
}

Node* push(Node* x,int id){return meld(x,create(w[id],id));}
Node* pop(Node* x){return meld(x->l,x->r);}

Node* heap[nmax];

void dfs(const auto &graph,int v,int p){

	for(auto &e:graph[v]){
		if(e.to==p) continue;
		dfs(graph,e.to,v);

		// e.toのheapから最小値
		while(heap[e.to]!=nullptr){
			int nid=heap[e.to]->id;
			if(uf->same(a[nid],b[nid])==false) break;
			heap[e.to]=pop(heap[e.to]);
		}

		ans[e.id]=-1;
		if(heap[e.to]!=nullptr){
			int nid=heap[e.to]->id;
			ans[e.id]=sum-w[e.id]+w[nid];
		}

		uf->unite(a[e.id],b[e.id]);
		heap[v]=meld(heap[v],heap[e.to]);
	}

}

int main(void){
	int n,m;
	cin >> n >> m;
	rep(i,m) cin >> a[i] >> b[i] >> w[i],a[i]--,b[i]--;

	using state=tuple<ll,int>; 
	vector<state> edges;
	rep(i,m) edges.push_back(state(w[i],i));
	sort(_all(edges));

	uf=new Union_find(n); 

	for(auto &e:edges){
		ll c,id;
		tie(c,id)=e;
		if(!uf->same(a[id],b[id])){
			ans[id]=1;
			uf->unite(a[id],b[id]);
			sum+=c;
		}		
	}

	bool ok=true;
	rep(i,n) if(uf->same(0,i)==false) ok=false;

	if(ok){
		G tree(n);
		rep(id,m){
			if(ans[id]==0){
				ans[id]=sum;
				heap[a[id]]=push(heap[a[id]],id);
				heap[b[id]]=push(heap[b[id]],id);
			}else
				add_edge(tree,a[id],b[id],id);
		}
		uf->init();
		dfs(tree,0,-1);
	}else{
		fill(ans,ans+m,-1);
	}

	rep(i,m) cout << ans[i] << endl;
	return 0;
}