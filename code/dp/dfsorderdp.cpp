for (int i=1,k=ID[i];i<=n;k=ID[++i]){
	for (int j=0;j<=m;j++) f[rt[k]+1][j]=max(f[rt[k]+1][j],f[i][j]);
	for (int j=m;~j;j--)
		if (j>=w[k] && f[i][j-w[k]]>=0)
			f[i][j]=f[i][j-w[k]]+p[k]; else f[i][j]=INF;
	s[k]--;
	for (int t=1;t<s[k];s[k]-=t,t<<=1)
		for (int j=m,W=t*w[k],P=t*p[k];j>=W;j--)
			f[i][j]=max(f[i][j],f[i][j-W]+P);
	if (s[k]) for (int j=m,W=s[k]*w[k],P=s[k]*p[k];j>=W;j--) 
				  f[i][j]=max(f[i][j],f[i][j-W]+P);
	for (int j=0;j<=m;j++) f[i+1][j]=max(f[i+1][j],f[i][j]);
}