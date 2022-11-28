void Stir2Row(int *S,int n){
	static int A[maxt+5],B[maxt+5];
	int t;for (t=1;t<=(n<<1);t<<=1);
	for (int i=0;i<=n;i++) A[i]=(i&1?MOD-INV[i]:INV[i]),B[i]=MUL(Pow(i,n),INV[i]);
	for (int i=n+1;i<t;i++) A[i]=B[i]=0;
	NTT(A,t,1);NTT(B,t,1);
	for (int i=0;i<t;i++) A[i]=MUL(A[i],B[i]);
	NTT(A,t,-1);
	for (int i=0;i<=n;i++) S[i]=A[i];
}