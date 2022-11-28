inline bool cmp(const int &i,const int &j) {return mp(X(i),Y(i))<mp(X(j),Y(j));}
void Solve(int L,int R){
	if (L==R) return;
	int mid=L+(R-L>>1);
	Solve(L,mid);
	int m=0;for (int i=L;i<=mid;i++) ID[++m]=i;
	sort(ID+1,ID+m+1,cmp);
	/* Make convex hull */
	if (!top) {Solve(mid+1,R);return;}
	for (int i=mid+1;i<=R;i++){
		int l=1,r=top-1;
		for (int mid=l+(r-l>>1);l<=r;mid=l+(r-l>>1))
			K(stk[mid],stk[mid+1])>=A(i)?r=mid-1:l=mid+1;
			// stk[mid] is better than stk[mid+1]
		f[i]=min(f[i],f[stk[l]]+val(stk[l]));
	}
	Solve(mid+1,R);
}