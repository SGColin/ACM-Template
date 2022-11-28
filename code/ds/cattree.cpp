#define L(i,k) ((i)>>(k)<<(k))
#define R(i,k) (((i)+(1<<(k))>>(k)<<(k))-1)

// maxs=(1<<LOG)
for (int j=1;j<LOG;j++) lg[1<<j]=j;
for (int i=1;i<maxs;i++) if (!lg[i]) lg[i]=lg[i-1];
for (int i=0;i<n;i++) A[0][i]=B[0][i]=a[i]; // a is the initial array
for (int j=1;(1<<j)<=n;j++){
	A[j][0]=0;B[j][n]=0; // initial value
	// calc(a,A) and calc(A,a) may be different
	for (int i=0;i<=n-1;i++) A[j][i]=(L(i,j)==i?a[i]:calc(a[i],A[j][i-1]));
	for (int i=n-1;i>=0;i--) B[j][i]=(R(i,j)==i?a[i]:calc(B[j][i+1],a[i]));
}