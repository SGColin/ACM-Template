void Divide(int x,int pre=0){
	vis[x]=true;fa[x]=pre;
	for (int j=lnk[x],u;j;j=nxt[j])
		if (!vis[u=to[j]])
			gr=0,S=si[u],getgr(u),Divide(gr,x);
}
void Insert(int &p,int pos,int k,int l=0,int r=n-1){
	if (!p) p=++pl;sum[p]+=k;
	if (l==r) return;
	int mid=l+(r-l>>1);
	pos<=mid?Insert(ls[p],pos,k,l,mid):Insert(rs[p],pos,k,mid+1,r);
}
int Ask(int p,int L,int R,int l=0,int r=n-1){
	if (!p) return 0;
	if (L==l && r==R) return sum[p];
	int mid=l+(r-l>>1);
	if (R<=mid) return Ask(ls[p],L,R,l,mid); 
	else if (L>mid) return Ask(rs[p],L,R,mid+1,r);
	else return Ask(ls[p],L,mid,l,mid)+Ask(rs[p],mid+1,R,mid+1,r);
}
void Update(int x,int y){
	for (int i=x;i;i=fa[i]){
		Insert(ro[i][0],Dis(x,i),y);
		if (fa[i]) Insert(ro[i][1],Dis(x,fa[i]),y);
	}
}
int Count(int x,int K){
	int ans=Ask(ro[x][0],0,K);
	for (int i=x;fa[i];i=fa[i]){
		int D=Dis(x,fa[i]);
		if (D<=K) ans+=Ask(ro[fa[i]][0],0,K-D)-Ask(ro[i][1],0,K-D);
	}
	return ans;
}