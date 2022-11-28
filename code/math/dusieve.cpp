map<int,int> f;
int Sum(int n){
	if (n<=maxs) return sum[n];
	if (f.count(n)) return f[n];
	int ans= ... ;
	for (int l=2,r;l<=n;l=r+1)
		r=n/(n/l),ans-= ... ;
	ans/= ... ;
	return f[n]=ans;
}