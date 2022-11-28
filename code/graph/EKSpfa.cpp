#define AM(x) ((x)+1<Maxn+5?(x)+1:0)
bool Spfa(int s,int t,LL &MF,LL &MC){
	for (int i=1;i<=Maxn;i++) dis[i]=1e18;MIN[t]=1e18;
	int Head=0,Tail=0;
	dis[s]=0;MIN[s]=1e18;vis[s]=true;que[++Tail]=s;
	while (Head!=Tail){
		int x=que[Head=AM(Head)];vis[x]=false;
		for (int j=lnk[x],u;j;j=nxt[j])
			if (e[j] && dis[x]+w[j]<dis[u=to[j]]){
				dis[u]=dis[x]+w[j];MIN[u]=min(MIN[x],(LL)e[j]);
				fa[u]=x;pre[u]=j;
				if (!vis[u]){
					que[Tail=AM(Tail)]=u;vis[u]=true;
					if (dis[u]<dis[AM(Head)]) swap(que[Tail],que[AM(Head)]);
				}
			}
	}
	if (MIN[t]==1e18) return false;
	MF+=MIN[t];MC+=dis[t]*MIN[t];
	for (int x=t,j=pre[x];x!=s;x=fa[x],j=pre[x]) e[j]-=MIN[t],e[j^1]+=MIN[t];
	return true;
}
void MCMF(int s,int t,LL &MF,LL &MC) {MF=MC=0;while (Spfa(s,t,MF,MC));}