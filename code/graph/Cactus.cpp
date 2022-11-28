void Cactus(int x,int pre=-1){
	dfn[x]=++dfn[0];
	for (int j=lnk[0][x],u;~j;j=nxt[j])
		if ((j^1)!=pre)
			if (!dfn[u=son[j]]) fa[u]=x,lst[u]=j,dis[u]=dis[x]+w[j],Cactus(u,j); else
			if (dfn[u]<dfn[x]){
				N++;Add(lnk[1],u,N,0);vis[j]=vis[j^1]=true;
				sum[N]=dis[x]-dis[u]+w[j];
				for (int i=x;i!=u;i=fa[i]){
					Add(lnk[1],N,i,min(dis[i]-dis[u],sum[N]-(dis[i]-dis[u])));
					vis[lst[i]]=vis[lst[i]^1]=true;
				}
			}
}
void DFS(int x,int fa=0){
	ST[x][0]=fa;dep[x]=dep[fa]+1;
	for (int j=1;j<=LOG;j++) ST[x][j]=ST[ST[x][j-1]][j-1];
	for (int j=lnk[1][x],u;~j;j=nxt[j])
		u=son[j],pre[u]=pre[x]+w[j],DFS(u,x);
}
int LCA(int &x,int &y){
	if (dep[x]<dep[y]) swap(x,y);
	for (int j=LOG;~j && dep[x]>dep[y];j--) if (dep[ST[x][j]]>=dep[y]) x=ST[x][j];
	if (x==y) return x;
	for (int j=LOG;~j;j--) if (ST[x][j]!=ST[y][j]) x=ST[x][j],y=ST[y][j];
	return ST[x][0];
}
int Dis(int x,int y){
	if (x==y) return 0;
	int fx=x,fy=y,lca=LCA(fx,fy);
	if (lca<=n) return pre[x]+pre[y]-(pre[lca]<<1);
	int ans=pre[x]-pre[fx]+pre[y]-pre[fy];
	if (dis[fx]>dis[fy]) swap(fx,fy);
	return ans+min(dis[fy]-dis[fx],sum[lca]-(dis[fy]-dis[fx]));
}
/* Build lnk[0] graph */
N=n;Cactus(1);
for (int i=1;i<=n;i++)
	for (int j=lnk[0][i];~j;j=nxt[j])
		if (!vis[j] && dfn[son[j]]>dfn[i]) Add(lnk[1],i,son[j],w[j]);
/* Make lnk[1] ST */