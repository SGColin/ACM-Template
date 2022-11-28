void Pow(int *F,int *a,int n,int b){
	if (!b) return;
	Pow(F,a,n,b>>1);
	NTT(F,n,1);for (int i=0;i<n;i++) F[i]=MUL(F[i],F[i]);
	NTT(F,n,-1);for (int i=n>>1;i<n;i++) F[i]=0;
	if (b&1){
		NTT(F,n,1);for (int i=0;i<n;i++) F[i]=MUL(F[i],a[i]);
		NTT(F,n,-1);for (int i=n>>1;i<n;i++) F[i]=0;
	}
}
void Stir2Col(int *S,int n,int m){
	static int F[maxt+5],G[maxt+5];
	int t;for (t=1;t<=(n<<1);t<<=1);
	G[0]=0;for (int i=1;i<=n;i++) G[i]=INV[i];
	for (int i=n+1;i<t;i++) G[i]=0;
	NTT(G,t,1);
	F[0]=1;for (int i=1;i<t;i++) F[i]=0;
	Pow(F,G,t,m);
	for (int i=0;i<=n;i++) S[i]=MUL(MUL(F[i],fac[i]),INV[m]);
}