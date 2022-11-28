void MTT(int *c,int *a,int n,int *b,int m){
	static int lg=15,BA=(1<<lg)-1;
	static CN A[maxt+5],P[maxt+5],Q[maxt+5];
	int t;for (t=1;t<=n+m;t<<=1);
	for (int i=0;i<=n;i++) P[i]=mp(a[i]&BA,a[i]>>lg);
	for (int i=n+1;i<t;i++) P[i]=mp(0,0);
	for (int i=0;i<=m;i++) Q[i]=mp(b[i]&BA,b[i]>>lg);
	for (int i=m+1;i<t;i++) Q[i]=mp(0,0);
	FFT(P,t,1);FFT(Q,t,1);
	for (int i=0;i<t;i++) A[i]=P[i];
	P[0]=mp((A[0].fr+A[0].fr)/2,(A[0].sc-A[0].sc)/2)*Q[0];
	Q[0]=mp((A[0].sc+A[0].sc)/2,(A[0].fr-A[0].fr)/2)*Q[0];
	for (int k=1,i=1,j;k<t;k<<=1)
		for (j=i^k-1;i<(k<<1);i++,j=i^k-1)
			P[i]=mp((A[i].fr+A[j].fr)/2,(A[i].sc-A[j].sc)/2)*Q[i],
			Q[i]=mp((A[i].sc+A[j].sc)/2,(A[j].fr-A[i].fr)/2)*Q[i];
	FFT(P,t,-1);FFT(Q,t,-1);
	for (int i=0;i<=n+m;i++){
		LL A0B0=LL(P[i].fr+0.5)%MOD,A0B1=LL(P[i].sc+0.5)%MOD;
		LL A1B0=LL(Q[i].fr+0.5)%MOD,A1B1=LL(Q[i].sc+0.5)%MOD;
		c[i]=(A0B0+(A0B1+A1B0<<lg)%MOD+(A1B1<<lg+lg)%MOD)%MOD;
	}
}