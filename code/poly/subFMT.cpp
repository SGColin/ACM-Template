for (int i=0;i<=n;i++){
	FMT(f[i],n,1);FMT(g[i],n,1);
	for (int j=0;j<=i;j++)
		for (int s=0;s<(1<<n);s++)
			h[i][s]=ADD(h[i][s],MUL(f[j][s],g[i-j][s]));
	FMT(h[i],n,-1);
}