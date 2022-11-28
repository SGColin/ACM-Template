void Sort(int n,int m){
	for (int i=0;i<=m;i++) ha[i]=0;for (int i=1;i<=n;i++) ha[rk[i]]++;
	for (int i=1;i<=m;i++) ha[i]+=ha[i-1];
	for (int i=n;i;i--) SA[ha[rk[sc[i]]]--]=sc[i];
}
void Make(char *s,int n,int m=255){ // notice s[i] can't be 0
	for (int i=1;i<=n;i++) rk[i]=s[i],sc[i]=i,sc[i+n]=0;Sort(n,m);
	for (int k=1,p=0;p<n;m=p,k<<=1){
		p=0;for (int i=n-k+1;i<=n;i++) sc[++p]=i;
		for (int i=1;i<=n;i++) if (SA[i]>k) sc[++p]=SA[i]-k;
		Sort(n,m);for (int i=1;i<=n;i++) sc[i]=rk[i];rk[SA[1]]=p=1;
		for (int i=2;i<=n;i++)
			rk[SA[i]]=(p+=sc[SA[i-1]]!=sc[SA[i]] || sc[SA[i-1]+k]!=sc[SA[i]+k]);
	}
	for (int i=1,k=0;i<=n;i++){
		if (rk[i]==1) continue;if (k) k--;
		while (s[i+k]==s[SA[rk[i]-1]+k]) k++;
		RMQ[0][rk[i]]=k;
	}
	for (int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for (int j=1;(1<<j)<n;j++)
		for (int i=2;i+(1<<j)-1<=n;i++)
			RMQ[j][i]=min(RMQ[j-1][i],RMQ[j-1][i+(1<<j-1)]);
}
int LCP(int x,int y){
	if (x>y) swap(x,y);x++;
	int k=lg[y-x+1];
	return min(RMQ[k][x],RMQ[k][y-(1<<k)+1]);
}