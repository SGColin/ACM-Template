int Linear(int *f,int *a,int K,int n){
	if (n<K) return f[n];
	static PN p,w,s;p.resize(K+1);
	for (int i=0;i<K;i++) p[i]=(MOD-a[K-i])%MOD;p[K]=1;
	w={0,1};w=w%p;
	for (s={1};n;n>>=1,w=w*w%p) if (n&1) s=s*w%p;
	int ans=0;
	for (int i=0,si=s.size();i<K && i<si;i++) ans=ADD(ans,MUL(s[i],f[i]));
	return ans;
}