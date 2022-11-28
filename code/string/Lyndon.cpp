// Duval algorithm
for (int i=1;i<=n;){
	int j=i,k=j+1;
	for (;k<=n && s[k]>=s[j];k++) s[k]==s[j]?j++:j=i;
	for (;i<=j;i+=k-j) L[++m]=i,R[m]=i+(k-j)-1;
}
// Minimal notation
for (int i=1;i<=n;){
	int j=i,k=j+1;
	for (;k<=n && s[k]>=s[j];k++) s[k]==s[j]?j++:j=i;
	for (;i<=j;i+=k-j) if (i<=(n>>1)) pos=i;
}
// Minimal suffix
for (int i=1;i<=n;){
	int j=i,k=j+1;
	ans[i]=i;
	for (;k<=n && s[k]>=s[j];k++)
		if (s[k]==s[j]) ans[k]=ans[j]+k-j,j++;
		else ans[k]=i,j=i;
	for (;i<=j;i+=k-j);
}
// Maximal suffix
for (int i=1;i<=n;){
	int j=i,k=j+1;
	if (!ans[i]) ans[i]=i;
	for (;k<=n && s[k]<=s[j];k++){
		if (!ans[k]) ans[k]=i;
		s[k]==s[j]?j++:j=i;
	}
	for (;i<=j;i+=k-j);
}