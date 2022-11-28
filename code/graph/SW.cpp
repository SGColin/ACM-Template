int getfa(int x) {return x==fat[x]?x:fat[x]=getfa(fat[x]);}
int Mincut(int te,int &s,int &t){
	val[0]=-2e9;
	for (int i=1;i<=n;i++) val[i]=0,vis[i]=false;
	for (t=fat[1];te;te--){
		s=t;vis[s]=true;
		for (auto x:e[s]) if (!vis[fat[x.fr]]) val[fat[x.fr]]+=x.sc;
		t=0;
		for (int i=1;i<=n;i++) if (!vis[fat[i]] && val[fat[i]]>val[t]) t=fat[i];
		if (!t) return 0;
	}
	return val[t];
}
void Merge(int s,int t){
	fat[t]=s;for (int i=1;i<=n;i++) getfa(i);
	for (int i=1;i<=n;i++) val[i]=0;
	for (auto x:e[s]) val[fat[x.fr]]+=x.sc;
	for (auto x:e[t]) val[fat[x.fr]]+=x.sc;
	e[s].clear();
	for (int i=1;i<=n;i++) if (val[i]) e[s].push_back(mp(i,val[i]));
}
int SW(){
	int ans=2e9;
	for (int i=1;i<=n;i++) fat[i]=i;
	for (int i=n-1,s,t;i;i--){
		ans=min(ans,Mincut(i,s,t));
		if (!ans) break;
		Merge(s,t);
	}
	return ans;
}