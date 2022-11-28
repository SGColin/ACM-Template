int vt[maxt+5],K,vn[maxt+5],top,stk[maxt+5];

#define Son(fa,x) (lt[fa]<=lt[x] && rt[x]<=rt[fa])
inline bool cmp(const int &i,const int &j) {return lt[i]<lt[j];}
void VT(){
	vn[++K]=ro;sort(vn+1,vn+1+K,cmp);
	int m=K;for (int i=2;i<=K;i++) vn[++m]=LCA(vn[i-1],vn[i]);
	sort(vn+1,vn+1+m,cmp);m=unique(vn+1,vn+1+m)-(vn+1);
	for (int i=1;i<=m;i++) /* Clear vt node */;
	top=0;
	for (int i=1;i<=m;i++){
		while (top && !Son(stk[top],vn[i])) top--;
		if (top) Add(vt,stk[top],vn[i]);
		stk[++top]=vn[i];
	}
}