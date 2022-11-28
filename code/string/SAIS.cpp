inline bool lmschar(int *tp,int x) {return x>0 && tp[x] && !tp[x-1];}
bool check(int *s,int *tp,int x,int y){
	if (s[x]!=s[y]) return false;
	for (x++,y++;!lmschar(tp,x) && !lmschar(tp,y);x++,y++)
		if (s[x]!=s[y]) return false;
	return s[x]==s[y];
}
void Sort(int *s,int *SA,int *tp,int *ha,int *lb,int *sb,int n,int m){
	for (int i=0;i<=n;i++)
		if (SA[i]>0 && !tp[SA[i]-1])
			SA[lb[s[SA[i]-1]]++]=SA[i]-1;
	for (int i=1;i<=m;i++) sb[i]=ha[i]-1;
	for (int i=n;i>=0;i--)
		if (SA[i]>0 && tp[SA[i]-1])
			SA[sb[s[SA[i]-1]]--]=SA[i]-1;
}
int* SAIS(int *s,int n,int m){
	int *SA=new int[n+1],*pos=new int[n+1],*ID=new int[n+1],*tp=new int[n+1];
	int *ha=new int[m+1],*lb=new int[m+1],*sb=new int[m+1];
	for (int i=0;i<=m;i++) ha[i]=0;for (int i=0;i<=n;i++) ha[s[i]]++;
	lb[0]=sb[0]=0;
	for (int i=1;i<=m;i++) ha[i]+=ha[i-1],lb[i]=ha[i-1],sb[i]=ha[i]-1;
	tp[n]=1;for (int i=n-1;i>=0;i--) tp[i]=(s[i]==s[i+1]?tp[i+1]:s[i]<s[i+1]);
	int cnt=0;
	for (int i=1;i<=n;i++) if (tp[i] && !tp[i-1]) pos[cnt++]=i;
	for (int i=0;i<=n;i++) SA[i]=-1;
	for (int i=0;i<cnt;i++) SA[sb[s[pos[i]]]--]=pos[i];
	Sort(s,SA,tp,ha,lb,sb,n,m);
	for (int i=0;i<=n;i++) ID[i]=-1;
	int tot=1;bool fl=false;
	for (int i=1,lst=-1,x;i<=n;i++)
		if (lmschar(tp,x=SA[i])){
			if (lst>=0 && !check(s,tp,x,lst)) tot++;
			if (lst>=0 && ID[lst]==tot) fl=true;
			ID[x]=tot;lst=x;
		}
	ID[n]=0;
	int *t=new int[cnt];
	for (int i=0,K=0;i<=n;i++) if (ID[i]>=0) t[K++]=ID[i];
	int *ST;
	if (!fl){
		ST=new int[cnt+1];
		for (int i=0;i<cnt;i++) ST[t[i]]=i;
	} else ST=SAIS(t,cnt-1,tot);
	lb[0]=sb[0]=0;
	for (int i=1;i<=m;i++) lb[i]=ha[i-1],sb[i]=ha[i]-1;
	for (int i=0;i<=n;i++) SA[i]=-1;
	for (int i=cnt-1;i>=0;i--) SA[sb[s[pos[ST[i]]]]--]=pos[ST[i]];
	Sort(s,SA,tp,ha,lb,sb,n,m);
	/* Delete if necessary
	delete[] pos;delete[] ID;delete[] tp;
	delete[] ha;delete[] lb;delete[] sb;
	delete[] t;delete[] ST;
	*/
	return SA;
}
void MakeSA(char *s,int n,int m=255){
	static int t[maxn+5];
	for (int i=1;i<=n;i++) t[i-1]=s[i];t[n]=0;
	SA=SAIS(t,n,m);
	for (int i=1;i<=n;i++) SA[i]++,rk[SA[i]]=i;
}
/* Delete if necessary
delete[] SA;
*/