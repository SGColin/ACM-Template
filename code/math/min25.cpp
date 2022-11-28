const int maxs=2*sqrt(maxn);
int S,N,a[maxs+5],g[maxs+5],ID[2][maxs+5];
int p[maxs+5];bool pri[maxs+5];

void Make(){
	for (int i=2;i<=maxs;i++){
		if (!pri[i]) p[++p[0]]=i;
		for (int j=1,t;j<=p[0] && (t=i*p[j])<=maxs;j++)
			{pri[t]=true;if (!(i%p[j])) break;}
	}
	// Make sum of f(p) and f(p^k)
}
#define id(x) ((x)<=S?ID[0][x]:ID[1][N/(x)])
int Sum(int a,int b){
	if (a<1 || p[b]>a) return 0;
	int ans=g[id(a)]-(sum of f[1,b-1]);
	for (int i=b;i<=p[0] && (LL)p[i]*p[i]<=a;i++){
		LL A=p[i],B=p[i]*p[i];
		for (int k=1;B<=a;k++,A=B,B*=p[i])
			ans=ans+Sum(a/A,i+1)*f(p[i]^k)+f(p[i]^(k+1));
	}
	return ans;
}
int Min25(int n){
	int m=0;S=sqrt(n);N=n;
	for (int l=1,r;l<=n;l=r+1){
		r=n/(n/l);a[++m]=n/l;g[m]=(sum of h[2,a[m]]);
		a[m]<=S?ID[0][a[m]]=m:ID[1][n/a[m]]=m;
	}
	for (int j=1;j<=p[0] && p[j]<=S;j++)
		for (int i=1;i<=m && (LL)p[j]*p[j]<=a[i];i++)
			g[i]=g[i]+h(p[j])*(sum of h[p[1],p[j-1]])-h(p[j])*g[id(a[i]/p[j])];
	// Update g
	return Sum(n,1)+f(1);
}