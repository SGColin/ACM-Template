inline void Spfa(int s){
	while (Head!=Tail){
		pair<int,int> now=que[Head=AM(Head)];
		int x=now.fr,y=now.sc;vis[x][y]=false;
		for (int t=0;t<4;t++){
			int xx=x+dif[t][0],yy=y+dif[t][1];
			if (xx<1 || xx>n || yy<1 || yy>m) continue;
			if (f[x][y][s]+cst[xx][yy]<f[xx][yy][s]){
				f[xx][yy][s]=f[x][y][s]+cst[xx][yy];
				if (!vis[xx][yy]) que[Tail=AM(Tail)]=mp(xx,yy),vis[xx][yy]=true;
			}
		}
	}
}

for (int s=1;s<(1<<K);s++){
	Head=0;Tail=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			for (int t=(s-1)&s;t;t=(t-1)&s)
				f[i][j][s]=min(f[i][j][s],f[i][j][t]+f[i][j][s^t]-cst[i][j]);
			if (f[i][j][s]<INF) que[Tail=AM(Tail)]=mp(i,j),vis[i][j]=true;
		}
	Spfa(s);
}