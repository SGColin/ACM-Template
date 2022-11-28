void DP(int x){
	int si=e[x].size();
	for (int j=0;j<si;j++) DP(e[x][j]);
	if (x>n){
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				F[0][i][j]=(i==j?f[e[x][0]][i]:-1e9);
		for (int i=1;i<si;i++)
			for (int j=0;j<2;j++){
				F[i][j][0]=max(F[i-1][j][0],F[i-1][j][1])+f[e[x][i]][0];
				F[i][j][1]=F[i-1][j][0]+f[e[x][i]][1];
			}
		f[x][0]=F[si-1][0][0];
		f[x][1]=-1e9;
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				if (i+j) f[x][1]=max(f[x][1],F[si-1][i][j]);
	} else {
		for (int j=0;j<si;j++) f[x][1]+=f[e[x][j]][0];f[x][1]++;
		for (int j=0;j<si;j++) f[x][0]+=max(f[e[x][j]][0],f[e[x][j]][1]);
	}
}