void FMT(int *a,int n,int f){ // or
	for (int i=0;i<n;i++)
		for (int s=1<<i;s<(1<<n);s=(s+1)|(1<<i))
			a[s]=ADD(a[s],f>0?a[s^(1<<i)]:MOD-a[s^(1<<i)]);
}
void FMT(int *a,int n,int f){ // and
	for (int i=0;i<n;i++)
		for (int s=1<<i;s<(1<<n);s=(s+1)|(1<<i))
			a[s^(1<<i)]=ADD(a[s^(1<<i)],f>0?a[s]:MOD-a[s]);
}