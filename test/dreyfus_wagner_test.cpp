#include <bits/stdc++.h>

#define _overload(_1,_2,_3,name,...) name
#define _rep(i,n) _range(i,0,n)
#define _range(i,a,b) for(int i=int(a);i<int(b);++i)
#define rep(...) _overload(__VA_ARGS__,_range,_rep,)(__VA_ARGS__)

using namespace std;

template<class T>bool chmax(T &a, const T &b) { return (a<b)?(a=b,1):0;}
template<class T>bool chmin(T &a, const T &b) { return (b<a)?(a=b,1):0;}

using G=vector<vector<int>>;

auto Dreyfus_wagner(const G &graph,const auto &term){
	using W=int; W inf=1<<28;
	const int n=int(graph.size()),t=int(term.size());
	if(t<=1) return 0;
	auto dist=graph;
	vector<vector<W>> opt(1<<t,vector<W>(n,inf));

	rep(k,n)rep(i,n)rep(j,n) chmin(dist[i][j],dist[i][k]+dist[k][j]);
	
	map<int,int> dict;
	rep(i,t){
		dict[term[i]]=1<<i;
		rep(j,n) opt[1<<i][j]=dist[term[i]][j];
		rep(j,t) opt[(1<<i)|(1<<j)][term[j]]=dist[term[i]][term[j]];
	}

	auto next_combination=[&](int s){
		int x=s&-s,y=s+x;
		return ((s&~y)/x>>1)|y;
    };

	rep(k,2,t){
		for(int s=(1<<k)-1;s<(1<<t);s=next_combination(s)){
			rep(i,n){
				int ns=s|dict[i];
				if(dict[i] and s==ns) continue;
				for(int u=(s-1)&s;u!=0;u=(u-1)&s){
					int c=s&(~u);
					chmin(opt[ns][i],opt[u][i]+opt[c][i]);
				}
			}
		}
		for(int s=(1<<k)-1;s<(1<<t);s=next_combination(s)){
			rep(i,n){
				int ns=s|dict[i];
				if(dict[i] and s==ns) continue;
				rep(j,n) chmin(opt[ns][i],opt[s][j]+dist[j][i]);
			}
		}
	}

	const int mask=(1<<t)-1;
	W ans=opt[mask][0];
	rep(i,n) chmin(ans,opt[mask][i]);
	return ans;
}

int main(void){
	int h,w;
	while(cin >> h >> w){
		if(h==0) break;
		const int inf=1<<28;

		G graph(h*w,vector<int>(h*w,inf));
		rep(i,h*w) graph[i][i]=0;
		vector<int> term;

		rep(i,h*w){
			int in;
			cin >> in;
			if(in) term.push_back(i);
		}
		
		rep(i,h)rep(j,w){
			const int cur=w*i+j;
			if(i+1<h) graph[cur][cur+w]=graph[cur+w][cur]=1;
			if(j+1<w) graph[cur][cur+1]=graph[cur+1][cur]=1;
		}
		int res=Dreyfus_wagner(graph,term);
		cout << h*w-1-res << endl;
	}
	return 0;
}