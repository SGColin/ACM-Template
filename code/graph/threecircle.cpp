inline bool cmp(const int &x,const int &y) {return d[x]<d[y] || d[x]==d[y] && x<y;}

for (int i=1;i<=m;i++) scanf("%d%d",&X[i],&Y[i]),d[X[i]]++,d[Y[i]]++,num[i]=0;
for (int i=1;i<=m;i++) cmp(X[i],Y[i])?Add(X[i],Y[i],i):Add(Y[i],X[i],i);
for (int i=1;i<=m;i++){
	ti++;for (int j=lnk[X[i]];j;j=nxt[j]) ID[to[j]]=w[j],vis[to[j]]=ti;
	for (int j=lnk[Y[i]];j;j=nxt[j])
		if (vis[to[j]]==ti) cnt[w[j]]++,cnt[ID[to[j]]]++,cnt[i]++,ans++;
}
/*use hint
ans is the number of three-circle
cnt[i] is the number of three-circle using edge i
*/