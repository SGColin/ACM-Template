int getg(int MOD){
	for (int i=2;i<MOD;i++){
		for (int j=1;j<=p[0] && (LL)p[j]*p[j]<=MOD;j++)
			if (!((MOD-1)%p[j])) if (Pow(i,(MOD-1)/p[j])==1) goto GG;
		return i;GG:continue;
	}
	return -1;
}
int Sqrt(int a){
	if (!a) return 0;
	int k=BSGS(g,a,MOD);
	return k<0 || (k&1)?-1:Pow(g,k>>1);
}