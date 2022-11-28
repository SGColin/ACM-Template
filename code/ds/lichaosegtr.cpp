inline Line Add(int a,int b,int c,int d){
	if (a==c) return Line(0,max(b,d),++tot);
	DB k=(DB)(d-b)/(c-a);return Line(k,b-k*a,++tot);
}
inline int fcmp(DB a,DB b) {if (fabs(a-b)<1e-8) return 0;if (a<b) return -1;return 1;}
#define Y(l,x) (l.k*(x)+l.b)
inline bool cmp(Line a,Line b,int pos){
	if (!fcmp(Y(a,pos),Y(b,pos))) return a.ID<b.ID;
	return fcmp(Y(a,pos),Y(b,pos))>0;
}
void Pushdown(Line x,int l,int r,int p){
	if (!tr[p].ID) {tr[p]=x;return;}if (cmp(x,tr[p],l)) swap(x,tr[p]);
	if (l==r||!fcmp(x.k,tr[p].k)) return;DB pos=(x.b-tr[p].b)/(tr[p].k-x.k);
	if (r<pos||pos<l) return;int mid=l+(r-l>>1);
	if (pos<=mid) Pushdown(tr[p],l,mid,LS),tr[p]=x; else Pushdown(x,mid+1,r,RS);
}
void Insert(int L,int R,Line x,int l=1,int r=maxn,int p=1){
	if (R<l||r<L) return;if (L<=l&&r<=R) return Pushdown(x,l,r,p);
	int mid=l+(r-l>>1);Insert(L,R,x,l,mid,LS);Insert(L,R,x,mid+1,r,RS);
}