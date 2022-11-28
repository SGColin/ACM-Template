const int maxp=10000,prime[]={2,3,5,7,11,13,17,19,23,29,31,37};

int P;LL p[maxp+5];
mt19937_64 mrand(19260817);

inline ULL ADD(ULL x,ULL y,ULL MOD) {return x+y>=MOD?x+y-MOD:x+y;}
inline ULL MUL(ULL x,ULL y,ULL MOD){
	LL s=x*y-(ULL)((DB)1/MOD*x*y)*MOD;
	return s<0?s+=MOD:(s>=MOD?s-=MOD:s);
}
LL Pow(LL w,LL b,LL MOD) {
	LL s;for (s=1;b;b>>=1,w=MUL(w,w,MOD)) if (b&1) s=MUL(s,w,MOD);return s;
}
bool check(LL p,LL n){
	int k=0;LL d=n-1,x,s;
	while (d&1^1) d>>=1,k++;
	x=Pow(p,d,n);
	for (;k;k--,x=s){
		s=MUL(x,x,n);
		if (s==1) return x==1 || x==n-1;
	}
	return false;
}
bool MR(LL n){
	for (int t=0;t<12;t++){
		if (n==prime[t]) return true;
		if (!(n%prime[t])) return false;
		if (!check(prime[t],n)) return false;
	}
	return true;
}
#define absi(x) ((x)<0?-(x):(x))
#define ctz __builtin_ctzll
LL gcd(LL a,LL b){
	if (!a) return b;if (!b) return a;
	int t=ctz(a|b);a>>=ctz(a);
	do {b>>=ctz(b);if (a>b) swap(a,b);b-=a;} while (b);
	return a<<t;
}
#define stp(x) (ADD(MUL(x,x,n),r,n))
LL FindD(LL n){
	if (n&1^1) return 2;
	static const int S=128;
	LL x=mrand()%n,r=mrand()%(n-1)+1;
	for (int l=1;;l<<=1){
		LL y=x,p=1;
		for (int i=0;i<l;i++) x=stp(x);
		for (int i=0;i<l;i+=S){
			LL z=x;
			for (int j=0;j<S && j<l-i;j++) x=stp(x),p=MUL(p,x+n-y,n);
			p=gcd(p,n);
			if (p==1) continue;if (p<n) return p;
			for (p=1,x=z;p==1;) x=stp(x),p=gcd(x+n-y,n);
			return p;
		}
	}
}
void PR(LL n){
	if (n==1) return;if (MR(n)) {p[++P]=n;return;}
	LL D;for (D=FindD(n);D==n;D=FindD(n));PR(D);PR(n/D);
}
// use hint: P=0;PR(n);