inline LL MUL(LL x,LL y,LL MOD) {return ((x*y-(LL)((DB)x/MOD*y)*MOD)%MOD+MOD)%MOD;}
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
LL exgcd(LL a,LL b,LL &x,LL &y){
	if (!b) return x=1,y=0,a;
	LL r=exgcd(b,a%b,y,x);y-=a/b*x;
	return r;
}
LL Solve(LL A,LL B,LL C){ // Ax=B(mod C)
	if (B<0) B+=C;LL x,y,r=exgcd(A,C,x,y);if (B%r) return -1;
	C/=r;x%=C;if (x<0) x+=C;x=MUL(B/r%C,x,C);return x;
}
#define lcm(A,B) ((A)/gcd((A),(B))*(B))
LL China(int n,LL *a,LL *m){ // x=a(mod m)
	LL A=a[1],M=m[1];
	for (int i=2;i<=n;i++){
		LL now=Solve(m[i],A-a[i],M);if (now<0) return -1;
		M=lcm(M,m[i]);A=MUL(now,m[i],M)+a[i];if (A>=M) A-=M;
	}
	return A;
}