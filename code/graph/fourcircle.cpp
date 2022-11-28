inline bool cmp(const int &x,const int &y) {return d[x]<d[y] || d[x]==d[y] && x<y;}

for (int i=1;i<=m;i++){
	scanf("%d%d",&X[i],&Y[i]);
	d[X[i]]++;d[Y[i]]++;
	e[X[i]].push_back(Y[i]);
	e[Y[i]].push_back(X[i]);
}
for (int i=1;i<=m;i++) cmp(X[i],Y[i])?Add(X[i],Y[i]):Add(Y[i],X[i]);
for (int x=1;x<=n;x++){
	for (auto y:e[x])
		for (int j=lnk[y];j;j=nxt[j])
			if (cmp(x,to[j])) ans+=cnt[to[j]],cnt[to[j]]++;
	for (auto y:e[x])
		for (int j=lnk[y];j;j=nxt[j])
			cnt[to[j]]=0;
}