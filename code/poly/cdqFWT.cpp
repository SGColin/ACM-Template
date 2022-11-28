void cdqFWT(int L,int R){
	if (L==R) {/*Update here*/ return;}
	int mid=L+(R-L>>1),t=R-L+1>>1;
	cdqFWT(mid+1,R);
	for (int i=mid+1;i<=R;i++) A[i-mid-1]=f[i];
	for (int i=0;i<t;i++) B[i]=p[i+t];
	FWT(A,t,1);FWT(B,t,1);
	for (int i=0;i<t;i++) A[i]=MUL(A[i],B[i]);
	FWT(A,t,-1);
	for (int i=L;i<=mid;i++) f[i]=ADD(f[i],A[i-L]);
	cdqFWT(L,mid);
}