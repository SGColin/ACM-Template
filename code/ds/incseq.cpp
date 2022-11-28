inline int Maxer(int x,int y) {return a[x]>a[y] || a[x]==a[y] && x>y?x:y;}
pair<int,int> Find(int L,int R,int p,int who){
	if (L==R) return a[L]>=a[who]?mp(1,L):mp(0,who);
	int mid=L+(R-L>>1);
	if (a[who]>a[MAX[p<<1]]) return Find(mid+1,R,p<<1|1,who); else {
		pair<int,int> ls=Find(L,mid,p<<1,who);
		return mp(ls.fr+res[p].fr,res[p].sc);
	}
}
void Build(int L,int R,int p=1){
	if (L==R) {MAX[p]=L;return;}
	int mid=L+(R-L>>1);
	Build(L,mid,p<<1);Build(mid+1,R,p<<1|1);
	MAX[p]=Maxer(MAX[p<<1],MAX[p<<1|1]);
	res[p]=Find(mid+1,R,p<<1|1,MAX[p<<1]);
}
void Update(int pos,int l=1,int r=n,int p=1){
	if (l==r) return;
	int mid=l+(r-l>>1);
	pos<=mid?Update(pos,l,mid,p<<1):Update(pos,mid+1,r,p<<1|1);
	MAX[p]=Maxer(MAX[p<<1],MAX[p<<1|1]);
	res[p]=Find(mid+1,r,p<<1|1,MAX[p<<1]);
}