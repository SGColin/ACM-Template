int n,now[maxn+5],MAX;
int gr,S,si[maxn+5],ms[maxn+5];bool vis[maxn+5];

void getgr(int x,int pre=0){
	si[x]=1;ms[x]=0;
	for (int j=lnk[x],u;j;j=nxt[j])
		if ((u=to[j])!=pre && !vis[u]){
			getgr(u,x);
			si[x]+=si[u];ms[x]=max(ms[x],si[u]);
		}
	ms[x]=max(ms[x],S-si[x]);
	if (!gr || ms[x]<ms[gr]) gr=x;
}
void getdep(int x,int dep=0,int pre=0){
	now[++now[0]]=dep;if (dep>MAX) MAX=dep;
	for (int j=lnk[x],u;j;j=nxt[j])
		if ((u=to[j])!=pre && !vis[u]) getdep(u,dep+1,x);
}
void Count(int f){
	int t;for (t=1;t<=(MAX<<1);t<<=1);
	for (int i=0;i<t;i++) F[i]=0;
	for (int i=1;i<=now[0];i++) F[now[i]]++;
	NTT(F,t,1);
	for (int i=0;i<t;i++) F[i]=MUL(F[i],F[i]);
	NTT(F,t,-1);
	for (int i=0;i<t;i++) sum[i]+=f*F[i];
}
void Divide(int x){
	vis[x]=true;
	now[0]=0;MAX=0;getdep(x);Count(1);
	for (int j=lnk[x],u;j;j=nxt[j])
		if (!vis[u=to[j]]){
			now[0]=0;MAX=0;getdep(u,1);Count(-1);
			gr=0;S=si[u];getgr(u);Divide(gr);
		}
}

gr=0;S=n;getgr(1);Divide(gr);