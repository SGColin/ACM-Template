// Brute force
bool DFS(int x){
	if (vis[x]) return true;
	if (vis[x^1]) return false;
	vis[x]=true;stk[++top]=x;
	for (int j=lnk[x];j;j=nxt[j])
		if (!DFS(to[j])) return false;
	return true;
}
bool Solve(){
	for (int i=0;i<(n<<1);i++) vis[i]=false;
	for (int i=0;i<(n<<1);i+=2)
		if (!vis[i] && !vis[i^1]){
			top=0;if (DFS(i)) continue;
			while (top) vis[stk[top--]]=false;
			if (!DFS(i^1)) return false;
		}
	return true;
}
// Tarjan
void Tarjan(int x){
	dfn[x]=low[x]=++ti;stk[++top]=x;instk[x]=true;
	for (int j=lnk[x];j;j=nxt[j])
		if (!dfn[to[j]]) Tarjan(to[j]),low[x]=min(low[x],low[to[j]]); else
		if (instk[to[j]]) low[x]=min(low[x],dfn[to[j]]);
	if (dfn[x]==low[x]){
		SCC[x]=++cnt;instk[x]=false;
		for (int y=stk[top--];y!=x;y=stk[top--]) SCC[y]=cnt,instk[y]=false;
	}
}
/* Build graph */
for (int i=0;i<(n<<1);i++) if (!dfn[i]) Tarjan(i);
for (int i=0;i<(n<<1);i+=2)
	if (SCC[i]==SCC[i^1]) goto GG;
	else ans[i>>1]=(SCC[i]<SCC[i^1]?0:1);