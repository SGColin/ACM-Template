int Sumpow(LL n,int K){
	static int sum[maxk+5],pre[maxk+5],suf[maxk+5];
	for (int i=1;i<=K+2;i++) sum[i]=ADD(sum[i-1],Pow(i,K));
	if (n<=(K+=2)) return sum[n];
	pre[0]=1;for (int i=1;i<=K;i++) pre[i]=MUL(pre[i-1],(n-i)%MOD);
	suf[K+1]=1;for (int i=K;i;i--) suf[i]=MUL(suf[i+1],(n-i)%MOD);
	int ans=0;
	for (int i=1;i<=K;i++){
		int U=MUL(pre[i-1],suf[i+1]);
		int D=MUL(INV[i-1],INV[K-i]);
		ans=ADD(ans,MUL(sum[i],MUL(U,K-i&1?MOD-D:D)));
	}
	return ans;
}