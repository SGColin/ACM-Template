void Find(int L,int R,int l=1,int r=n,int p=1){
	if (answer is already found) return;
	if (L==l && r==R){
		if ([l,r] is impossible) return;
		if (l==r) {answer is found; return;} // single point
		int mid=l+(r-l>>1); Pushdown(p);
		if (...) Find(L,mid,l,mid,p<<1); else Find(mid+1,R,mid+1,r,p<<1|1);
		return;
	}
	int mid=l+(r-l>>1); Pushdown(p);
	if (R<=mid) Find(L,R,l,mid,p<<1); else if (L>mid) Find(L,R,mid+1,r,p<<1|1); else{
		Find(L,mid,l,mid,p<<1);
		if (answer is already found) return;
		Find(mid+1,R,mid+1,r,p<<1|1);
	}
}