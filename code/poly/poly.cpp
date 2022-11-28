inline int ADD(int x,int y) {return x+y>=MOD?x+y-MOD:x+y;}
inline int MUL(int x,int y) {return (LL)x*y%MOD;}
int Pow(int w,int b) {int s;for (s=1;b;b>>=1,w=MUL(w,w)) if (b&1) s=MUL(s,w);return s;}
__attribute__((constructor)) void NTTPre(){
	int x=Pow(3,(MOD-1)/maxt);
	wn[maxt>>1]=1;
	for (int i=(maxt>>1)+1;i<maxt;i++) wn[i]=MUL(wn[i-1],x);
	for (int i=(maxt>>1)-1;i;i--) wn[i]=wn[i<<1];
}
void NTT(int *a,int n,int f){
	if (f>0){
		for (int k=n>>1;k;k>>=1)
			for (int i=0;i<n;i+=k<<1)
				for (int j=0;j<k;j++){
					int x=a[i+j],y=a[i+j+k];
					a[i+j+k]=MUL(x+MOD-y,wn[k+j]);
					a[i+j]=ADD(x,y);
				}
	} else {
		for (int k=1;k<n;k<<=1)
			for (int i=0;i<n;i+=k<<1)
				for (int j=0;j<k;j++){
					int x=a[i+j],y=MUL(a[i+j+k],wn[k+j]);
					a[i+j+k]=ADD(x,MOD-y);
					a[i+j]=ADD(x,y);
				}
		for (int i=0,INV=MOD-(MOD-1)/n;i<n;i++) a[i]=MUL(a[i],INV);
		reverse(a+1,a+n);
	}
}
void Make(int n){
	INV[0]=INV[1]=1;for (int i=2;i<=n;i++) INV[i]=MUL(MOD-MOD/i,INV[MOD%i]);
	fac[0]=1;for (int i=1;i<=n;i++) fac[i]=MUL(fac[i-1],i),INV[i]=MUL(INV[i-1],INV[i]);
}
void Inte(int *F,int *a,int n,int K){ // F=integral(a)
	for (int i=n+K;i>=K;i--) F[i]=MUL(a[i-K],MUL(INV[i],fac[i-K]));
	for (int i=0;i<K;i++) F[i]=0;
}
void Deri(int *F,int *a,int n,int K){ // F=a'
	for (int i=0;i<=n-K;i++) F[i]=MUL(a[i+K],MUL(fac[i+K],INV[i]));
	for (int i=n-K+1;i<=n;i++) F[i]=0;
}
void Inv(int *F,int *a,int n){ // F=1/a
	if (n==1) {F[0]=Pow(a[0],MOD-2);return;}
	Inv(F,a,n>>1);
	for (int i=0;i<n;i++) temA[i]=a[i],temA[i+n]=F[i+n]=0;
	NTT(temA,n<<1,1);NTT(F,n<<1,1);
	for (int i=0;i<(n<<1);i++) temA[i]=MUL(F[i],2+MOD-MUL(temA[i],F[i]));
	NTT(temA,n<<1,-1);for (int i=0;i<n;i++) F[i]=temA[i],F[i+n]=0;
}
void Ln(int *F,int *a,int n){ // F=ln(a)
	Inv(temB,a,n);
	Deri(temA,a,n-1,1);for (int i=0;i<n;i++) temA[i+n]=0;
	NTT(temA,n<<1,1);NTT(temB,n<<1,1);
	for (int i=0;i<(n<<1);i++) temA[i]=MUL(temA[i],temB[i]);
	NTT(temA,n<<1,-1);Inte(F,temA,n-2,1);
}
void Exp(int *F,int *a,int n){ // F=exp(a)
	if (n==1) {F[0]=1;return;} // only when a[0]=0
	Exp(F,a,n>>1);Ln(temA,F,n);
	for (int i=0;i<n;i++) temA[i]=ADD(a[i],MOD-temA[i]),temA[i+n]=F[i+n]=0;
	temA[0]=ADD(temA[0],1);
	NTT(temA,n<<1,1);NTT(F,n<<1,1);
	for (int i=0;i<(n<<1);i++) temA[i]=MUL(temA[i],F[i]);
	NTT(temA,n<<1,-1);for (int i=0;i<n;i++) F[i]=temA[i],F[i+n]=0;
}
void Sqrt(int *F,int *a,int n){ // F=sqrt(a)
	if (n==1) {F[0]=1;return;} // only when a[0]=1
	Sqrt(F,a,n>>1);Inv(temB,F,n);
	for (int i=0;i<n;i++) temA[i]=a[i],temA[i+n]=0;
	NTT(temA,n<<1,1);NTT(temB,n<<1,1);
	for (int i=0;i<(n<<1);i++) temA[i]=MUL(temA[i],temB[i]);
	NTT(temA,n<<1,-1);for (int i=0;i<n;i++) F[i]=MUL(F[i]+temA[i],INV2),F[i+n]=0;
}
inline PN operator + (const PN &a,const PN &b){
	static PN c;c.resize(max(a.size(),b.size()));
	for (int i=0;i<c.size();i++) c[i]=ADD(i<a.size()?a[i]:0,i<b.size()?b[i]:0);
	return c;
}
inline PN operator - (const PN &a,const PN &b){
	static PN c;c.resize(max(a.size(),b.size()));
	for (int i=0;i<c.size();i++) c[i]=ADD(i<a.size()?a[i]:0,i<b.size()?MOD-b[i]:0);
	return c;
}
PN operator * (const PN &a,const PN &b){
	static PN c;
	int n=a.size(),m=b.size(),t;
	for (t=1;t<n+m-1;t<<=1);
	for (int i=0;i<n;i++) temA[i]=a[i];for (int i=n;i<t;i++) temA[i]=0;
	for (int i=0;i<m;i++) temB[i]=b[i];for (int i=m;i<t;i++) temB[i]=0;
	NTT(temA,t,1);NTT(temB,t,1);
	for (int i=0;i<t;i++) temA[i]=MUL(temA[i],temB[i]);
	NTT(temA,t,-1);
	c.resize(n+m-1);for (int i=0;i<n+m-1;i++) c[i]=temA[i];
	return c;
}
inline PN operator / (const PN &a,const PN &b){
	static int C[maxt+5];static PN c;
	int n=a.size()-1,m=b.size()-1;
	if (n<m) return {0};
	int t;for (t=1;t<n-m+1;t<<=1);
	for (int i=0;i<n-m+1;i++) temB[i]=m-i<0?0:b[m-i];
	for (int i=n-m+1;i<t;i++) temB[i]=0;
	Inv(C,temB,t);
	for (int i=0;i<n-m+1;i++) temA[i]=a[n-i];
	for (int i=n-m+1;i<(t<<1);i++) temA[i]=0;
	NTT(temA,t<<1,1);NTT(C,t<<1,1);
	for (int i=0;i<(t<<1);i++) C[i]=MUL(temA[i],C[i]);
	NTT(C,t<<1,-1);
	c.resize(n-m+1);for (int i=0;i<n-m+1;i++) c[i]=C[n-m-i];
	return c;
}
inline PN operator % (const PN &a,const PN &b) {
	static PN c;c=a-a/b*b;c.resize(b.size()-1);return c;
}
void Build(int L,int R,int p=1){
	if (L==R) {P[p]={(MOD-X[L])%MOD,1};return;}
	int mid=L+(R-L>>1);
	Build(L,mid,p<<1);Build(mid+1,R,p<<1|1);
	P[p]=P[p<<1]*P[p<<1|1];
}
void getv(int L,int R,int p=1){
	if (L==R) {v[L]=F[0];return;}
	int mid=L+(R-L>>1);PN tem=F;
	F=tem%P[p<<1];getv(L,mid,p<<1);
	F=tem%P[p<<1|1];getv(mid+1,R,p<<1|1);
}
PN Lag(int L,int R,int p=1){
	if (L==R) return {v[L]};
	int mid=L+(R-L>>1);
	return P[p<<1|1]*Lag(L,mid,p<<1)+P[p<<1]*Lag(mid+1,R,p<<1|1);
}