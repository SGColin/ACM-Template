int tem[maxt+5],*pl=tem,*f[maxn+5],*g[maxn+5],ans;

void DFS(int x,int pre=0){
	dep[x]=dep[pre]+1;md[x]=dep[x];
	for (int j=lnk[x];j;j=nxt[j])
		if (to[j]!=pre){
			DFS(to[j],x);
			if (md[to[j]]>md[x]) md[x]=md[to[j]],SH[x]=to[j];
		}
	len[x]=len[SH[x]]+1;
}
void LSD(int x,int lst){
	top[x]=lst;
	if (SH[x]) LSD(SH[x],lst);
	for (int j=lnk[x];j;j=nxt[j])
		if (to[j]!=SH[x]) LSD(to[j],to[j]);
}
int getanc(int x,int k){
	if (!k) return x;
	int t=lg[k];
	x=ST[t][x];k-=1<<t;k-=dep[x]-dep[top[x]];x=top[x];
	if (!k) return x;
	return k>0?U[x][k-1]:D[x][-k-1];
}
void DP(int x,int pre=0,bool fl=true){
	if (fl) f[x]=pl,pl+=len[x],g[x]=pl+len[x]-1,pl+=len[x]<<1;
	if (SH[x]) f[SH[x]]=f[x]+1,g[SH[x]]=g[x]-1,DP(SH[x],x,false);
	f[x][0]++;
	for (int j=lnk[x],u;j;j=nxt[j])
		if ((u=to[j])!=pre && u!=SH[x]){
			DP(u,x,true);
			for (int j=0;j<len[u];j++){
				ans+=f[u][j]*g[x][j+1];
				if (j>1) ans+=f[x][j-1]*g[u][j];
			}
			for (int j=0;j<len[u];j++){
				g[x][j+1]+=f[x][j+1]*f[u][j];
				f[x][j+1]+=f[u][j];
				if (j) g[x][j-1]+=g[u][j];
			}
		}
	ans+=g[x][0];
}

DFS(1);LSD(1,1);
for (int i=1;i<=n;i++)
	if (i==top[i]){
		U[i]=pl;pl+=len[i];D[i]=pl;pl+=len[i];
		for (int j=0,x=i,y=i;j<len[i];j++)
			x=fa[x],U[i][j]=x,y=SH[y],D[i][j]=y;
	}