vector<int> query(q);
iota(begin(query),end(query),0);
sort(begin(query), end(query), [&](int a, int b){
	if(l[a] / B != l[b] / B) return l[a] < l[b];
	return bool((r[a] < r[b]) ^ (l[a] / B % 2));
});

int lft = 0, rht = 0;
for(auto &i:query){
	const int nl = l[i],nr = r[i];
	while(rht < nr)  inc(rht++);
	while(nl < lft)  inc(--lft);
	while(nr < rht)  dec(--rht);
	while(lft < nl)  dec(lft++);
	ans[i] = calc();
}