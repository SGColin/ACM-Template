inline int fcmp(DB a,DB b) {return fabs(a-b)<eps?0:(a<b?-1:1);}
bool check(DB mid){
	DB U=Max(d[i]-2*p[i]);
	/* Calculate w[x][y] and p[i] */
	E=1;for (int i=0;i<=Maxn;i++) lnk[i]=0,d[i]=0;
	for (int i=1;i<=m;i++)
		Add(x[i],y[i],w[i]),Add(y[i],x[i],w[i]),
		d[x[i]]+=w[i],d[y[i]]+=w[i];
	for (int i=1;i<=n;i++) Add(S,i,U),Add(i,T,U+2*p[i]-d[i]);
	return fcmp(U*n,Dinic(S,T))>0;
}