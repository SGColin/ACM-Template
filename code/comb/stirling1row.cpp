void Stir1Row(int *S,int n){
	static int F[maxt+5],G[maxt+5];
	if (n==0) {S[0]=1;return;}
	if (n==1) {S[0]=0;S[1]=1;return;}
	int m=n>>1;Stir1Row(S,m);
	for (int i=0,pw=1;i<=m;i++,pw=MUL(pw,m))
		F[i]=MUL(S[m-i],fac[m-i]),G[i]=MUL(pw,INV[i]);
	int t;for (t=1;t<=(m<<1);t<<=1);
	for (int i=m+1;i<t;i++) F[i]=G[i]=0;
	NTT(F,t,1);NTT(G,t,1);
	for (int i=0;i<t;i++) F[i]=MUL(F[i],G[i]);
	NTT(F,t,-1);reverse(F,F+m+1);
	for (int i=0;i<=m;i++) F[i]=MUL(F[i],INV[i]),G[i]=S[i];
	for (int i=m+1;i<t;i++) F[i]=G[i]=0;
	NTT(F,t,1);NTT(G,t,1);
	for (int i=0;i<t;i++) F[i]=MUL(F[i],G[i]);
	NTT(F,t,-1);
	for (int i=0;i<=n;i++) S[i]=F[i];
	if (n&1) for (int i=n;~i;i--) S[i]=ADD(MUL(S[i],n-1),i?S[i-1]:0);
}