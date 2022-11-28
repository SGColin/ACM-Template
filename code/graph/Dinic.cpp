bool BFS(int s,int t){
	int Head=0,Tail=0;
	dis[s]=0;cur[s]=lnk[s];que[++Tail]=s;vis[s]=++ti;
	while (Head!=Tail){
		int x=que[++Head];
		for (int j=lnk[x],u;j;j=nxt[j])
			if (e[j] && vis[u=to[j]]<ti)
				dis[u]=dis[x]+1,cur[u]=lnk[u],que[++Tail]=u,vis[u]=ti;
	}
	return vis[t]==ti;
}
LL DFS(int x,int t,int MIN=2147483647){
	if (x==t || !MIN) return MIN;
	LL f=0;int now;
	for (int &j=cur[x];j;j=nxt[j])
		if (dis[x]+1==dis[to[j]] && (now=DFS(to[j],t,min(MIN,e[j]))))
			{e[j]-=now;e[j^1]+=now;f+=now;if (!(MIN-=now)) break;}
	return f;
}
LL Dinic(int s,int t) {LL MF=0;while (BFS(s,t)) MF+=DFS(s,t);return MF;}