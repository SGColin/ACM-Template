struct Point{
	int x[2],w;
	bool operator < (const Point &a) {return x[D]<a.x[D];}
}a[maxn+5];
int que[maxn+5];
int ro,son[maxn+5][2],MN[maxn+5][2],MX[maxn+5][2],val[maxn+5];
inline bool cmp(const int &i,const int &j) {return a[i]<a[j];}
void Pushup(int p){
	for (int i=0;i<2;i++) MN[p][i]=MX[p][i]=a[p].x[i];
	val[p]=max(a[p].w,max(val[son[p][0]],val[son[p][1]]));
	sum[p]=sum[son[p][0]]+a[p].w+sum[son[p][1]];
	for (int j=0;j<2;j++)
		if (son[p][j])
			for (int i=0;i<2;i++)
				MN[p][i]=min(MN[p][i],MN[son[p][j]][i]),
				MX[p][i]=max(MX[p][i],MX[son[p][j]][i]);
}
int Build(int L,int R,int d=0){
	int m=L+(R-L>>1);
	D=d;nth_element(que+L,que+m,que+R+1,cmp);
	int p=que[m];son[p][0]=son[p][1]=0;
	if (L<m) son[p][0]=Build(L,m-1,d^1);
	if (m<R) son[p][1]=Build(m+1,R,d^1);
	Pushup(p);return p;
}
#define absi(x) ((x)<0?-(x):(x))
#define TOP(p,x,y) (max(absi((x)-MX[p][0]),absi((x)-MN[p][0]))
						+max(absi((y)-MX[p][1]),absi((y)-MN[p][1])))
int VAL(int p,int x,int y){
	if (!p) return 0;
	return min(TOP(p,x,y),val[p]);
}
void Ask(int p,int x,int y){ // optimize
	if (val[p]<=ans || TOP(p,x,y)<=ans) return;
	ans=max(ans,min(absi(x-a[p].x[0])+absi(y-a[p].x[1]),a[p].w));
	int d=VAL(son[p][1],x,y)>VAL(son[p][0],x,y);
	if (son[p][d]) Ask(son[p][d],x,y);if (son[p][d^1]) Ask(son[p][d^1],x,y);
}
int Ask(int p,int A,int B,int C,int D){ // matrix, x in [A,B], y in [C,D]
	if (!p || B<MN[p][0] || MX[p][0]<A || D<MN[p][1] || MX[p][1]<C) return 0;
	if (A<=MN[p][0] && MX[p][0]<=B && C<=MN[p][1] && MX[p][1]<=D) return sum[p];
	int val=(A<=a[p].x[0] && a[p].x[0]<=B && C<=a[p].x[1] && a[p].x[1]<=D?a[p].w:0);
	return Ask(son[p][0],A,B,C,D)+val+Ask(son[p][1],A,B,C,D);
}