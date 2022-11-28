int Asknth(int *U,int *D,int m,int n){
	static int A[maxt+5];
	int t;for (t=1;t<=(m<<1);t<<=1);
	Inv(A,D,t>>1);NTT(A,t,1);NTT(U,t,1);
	for (int i=0;i<t;i++) A[i]=MUL(A[i],U[i]);
	NTT(A,t,-1);
	if (n<=m) return A[n];
	for (int i=0;i<m;i++) A[i]=A[i+1];
	for (int i=1,INV=Pow(D[0],MOD-2);i<=m;i++) D[i]=MUL(MOD-D[i],INV);
	return Linear(A,D,m,n-1);
}