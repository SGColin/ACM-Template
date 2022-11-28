void Tarjan(int x,int pre=-1){
	dfn[x]=low[x]=++ti;stk[++top]=x;
	for (int j=lnk[0][x],u;~j;j=nxt[j])
		if ((j^1)!=pre)
			if (!dfn[u=son[j]]){
				Tarjan(u,j);low[x]=min(low[x],low[u]);
				if (low[u]>=dfn[x]){
					N++;Add(1,x,N);
					for (int y=stk[top--];;y=stk[top--]) {Add(1,N,y);if (y==u) break;}
				}
			} else low[x]=min(low[x],dfn[u]);
}