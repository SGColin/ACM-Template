void DFS(int x,int pre=0){
	si[x]=1;fa[x]=pre;
	for (int j=lnk[x];j;j=nxt[j])
		if (to[j]!=pre){
			DFS(to[j],x);si[x]+=si[to[j]];
			if (si[to[j]]>si[SH[x]]) SH[x]=to[j];
		}
}
void HLD(int x,int lst){
	lt[x]=++lt[0];top[x]=lst;btm[x]=x;
	if (SH[x]) HLD(SH[x],lst),btm[x]=btm[SH[x]];
	for (int j=lnk[x];j;j=nxt[j])
		if (to[j]!=fa[x] && to[j]!=SH[x]) HLD(to[j],to[j]);
}
Matrix operator * (const Matrix &a,const Matrix &b){
	static Matrix c;c.zero();
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			for (int k=0;k<2;k++)
				c.s[i][j]=max(c.s[i][j],a.s[i][k]+b.s[k][j]);
	return c;
}
void Build(int x,bool fl=true){
	if (SH[x]) Build(SH[x],false);
	sum[x][1]=a[x];
	for (int j=lnk[x],u;j;j=nxt[j])
		if ((u=to[j])!=fa[x] && u!=SH[x]){
			Build(u,true);
			sum[x][0]+=max(f[u][0],f[u][1]);
			sum[x][1]+=f[u][0];
		}
	Update(lt[x],sum[x][0],sum[x][1]);
	if (fl){
		tem=Ask(lt[x],lt[btm[x]]);
		f[x][0]=tem.s[0][0];f[x][1]=tem.s[0][1];
	}
}
void Modify(int x,int y){ // Modify a[x] to y
	LL lst[2]={0,y-a[x]};a[x]=y;
	for (;x;x=fa[x]){
		Update(lt[x],lst[0],lst[1]);
		sum[x][0]+=lst[0];sum[x][1]+=lst[1];
		x=top[x];tem=Ask(lt[x],lt[btm[x]]);
		lst[0]=max(tem.s[0][0],tem.s[0][1])-max(f[x][0],f[x][1]);
		lst[1]=tem.s[0][0]-f[x][0];
		f[x][0]=tem.s[0][0];f[x][1]=tem.s[0][1];
	}
}

DFS(1);HLD(1,1);Build(1);