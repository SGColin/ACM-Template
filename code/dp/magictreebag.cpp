void DP(int x,int pre=0){
	si[x]=1;
	for (int j=lnk[x],u;j;j=nxt[j])
		if ((u=to[j])!=pre){
			DP(u,x);
			for (int i=min(si[x]+si[u],K);~i;i--)
				for (int k=max(i-si[x],0);k<=si[u] && k<=i;k++)
					f[x][i]=max(f[x][i],f[x][i-k]+f[u][k]+val(k));
			si[x]+=si[u];
		}
}