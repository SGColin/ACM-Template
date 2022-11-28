int LCA(int x,int y){
	x=fa[x];y=fa[y];
	for (ti++;vis[x]<ti;swap(x,y)) if (x) vis[x]=ti,x=fa[pre[who[x]]];
	return x;
}
void Blossom(int x,int y,int lca){
	while (fa[x]!=lca){
		pre[x]=y;y=who[x];
		if (tp[y]) tp[y]^=1,que[++Tail]=y;
		fa[x]=fa[y]=lca;x=pre[y];
	}
}
bool Find(int x){
	for (int i=1;i<=n;i++) fa[i]=i,tp[i]=-1,pre[i]=0;
	Head=0;Tail=0;que[++Tail]=x;tp[x]=0;
	while (Head!=Tail){
		int x=que[++Head];
		for (int j=lnk[x],u;j;j=nxt[j])
			if (tp[u=son[j]]<0){
				tp[u]=1;pre[u]=x;
				if (!who[u]){
					for (int p=u,lst;p;p=lst)
						lst=who[pre[p]],who[p]=pre[p],who[pre[p]]=p;
					return true;
				}
				tp[who[u]]=0;que[++Tail]=who[u];
			} else if (tp[u]==0){
				int lca=LCA(x,u);Blossom(x,u,lca);Blossom(u,x,lca);
			}
	}
	return false;
}
for (int i=1,x,y;i<=m;i++) scanf("%d%d",&x,&y),Add(x,y),Add(y,x);
for (int i=1;i<=n;i++) if (!who[i]) ans+=Find(i);