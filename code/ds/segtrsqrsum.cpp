struct Matrix{
	int s[4][4];
	void zero() {for (int i=0;i<4;i++) for (int j=0;j<4;j++) s[i][j]=0;}
	void unit() {zero();for (int i=0;i<4;i++) s[i][i]=1;}
};
int M[maxt+5][4],cnt[maxt+5];Matrix tag[maxt+5],tem;
#define ADD(x,y) (((x)+(y))%MOD)
#define MUL(x,y) ((LL)(x)*(y)%MOD)
Matrix operator * (const Matrix &a,const Matrix &b){
	static Matrix c;c.zero();
	for (int i=0;i<4;i++)
		for (int j=i;j<4;j++)
			for (int k=i;k<=j;k++)
				c.s[i][j]=ADD(c.s[i][j],MUL(a.s[i][k],b.s[k][j]));
	return c;
}
void Make(int k){ // the matrix of tag k
	tem.unit();
	tem.s[0][1]=k;tem.s[0][2]=MUL(k,k);tem.s[0][3]=MUL(k,k);
	tem.s[1][2]=ADD(k,k);tem.s[1][3]=ADD(k,k);
	tem.s[2][3]=1;
}
void Mul(int *a,Matrix &A){
	static int b[4];
	b[0]=b[1]=b[2]=b[3]=0;
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			b[i]=ADD(b[i],MUL(a[j],A.s[j][i]));
	a[0]=b[0];a[1]=b[1];a[2]=b[2];a[3]=b[3];
}
void Build(int L,int R,int p=1){
	M[p][0]=R-L+1;tag[p].unit();
	if (L==R) {M[p][1]=a[L];M[p][2]=MUL(a[L],a[L]);M[p][3]=M[p][2];return;}
	int mid=L+(R-L>>1);
	Build(L,mid,p<<1);Build(mid+1,R,p<<1|1);
	for (int i=1;i<4;i++) M[p][i]=ADD(M[p<<1][i],M[p<<1|1][i]);
}
inline void Addtag(int p,Matrix &A) {Mul(M[p],A);tag[p]=tag[p]*A;cnt[p]++;}
void Pushdown(int p) {
	if (cnt[p]) Addtag(p<<1,tag[p]),Addtag(p<<1|1,tag[p]),cnt[p]=0,tag[p].unit();
}
void Insert(int L,int R,int l=1,int r=n,int p=1){
	if (L==l && r==R) return Addtag(p,tem);
	int mid=l+(r-l>>1);Pushdown(p);
	if (R<=mid) Insert(L,R,l,mid,p<<1); else if (L>mid) Insert(L,R,mid+1,r,p<<1|1);
	else Insert(L,mid,l,mid,p<<1),Insert(mid+1,R,mid+1,r,p<<1|1);
	for (int i=1;i<4;i++) M[p][i]=ADD(M[p<<1][i],M[p<<1|1][i]);
}
int Ask(int L,int R,int l=1,int r=n,int p=1){
	if (L==l && r==R) return M[p][3];
	int mid=l+(r-l>>1);Pushdown(p);
	if (R<=mid) return Ask(L,R,l,mid,p<<1); 
	else if (L>mid) return Ask(L,R,mid+1,r,p<<1|1);
	else return ADD(Ask(L,mid,l,mid,p<<1),Ask(mid+1,R,mid+1,r,p<<1|1));
}
// use hint
if (l[i]>1) Make(0),Insert(1,l[i]-1);
Make(X[i]);Insert(l[i],r[i]);
if (r[i]<n) Make(0),Insert(r[i]+1,n);