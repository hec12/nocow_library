struct Compress{
	using T=ll;
	vector<T> ary;
    void push_back(T x){ary.push_back(x);}
    void init(){
    	sort(begin(ary),end(ary));
	    ary.erase(unique(begin(ary),end(ary)),end(ary));
    }
	int size(){return int(ary.size());}
	int zip(T x){return lower_bound(begin(ary),end(ary),x)-begin(ary);}
	T unzip(int i){return ary[i];}
};
