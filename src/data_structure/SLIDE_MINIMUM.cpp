// スライド最小値 

void add(auto &deq,ll x){
	while(!deq.empty()and deq.back()>x) deq.pop_back();
	deq.push_back(x);
}

void del(auto &deq,ll x){
	if(!deq.empty() and deq.front()==x) deq.pop_front();
}

ll getval(auto &deq){
	return (deq.empty())?inf:deq.front();
}