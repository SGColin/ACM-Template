const int maxa=...; // the range of (A,B,C)

int f[maxa+5][maxa+5][maxa+5];
int m;pair<int, pair<int,int> > a[maxm+5]; // a is array of points
set< pair<int,int> > S;set< pair<int,int> >::iterator it;

for (int i=1;i<=n;i++){
	readi(m);
	for (int i=1;i<=m;i++) readi(a[i].A),readi(a[i].B),readi(a[i].C);
	sort(a+1,a+1+m);
	S.clear();S.insert(mp(0,maxa+1));S.insert(mp(maxa+1,0));
	for (int i=1;i<=m;i++){
		int A=a[i].A;pair<int,int> p=a[i].sc;
		it=prev(S.upper_bound(p));
		if (it->sc<=p.sc) continue;
		Update(A,it,-1);
		for (it++;it->sc>=p.sc;it=S.erase(it)) Update(A,it,-1);
		it=S.insert(p).fr;
		Update(A,it,1);Update(A,--it,1);
	}
}
for (int i=1;i<=maxa;i++)
	for (int j=1;j<=maxa;j++)
		for (int k=1;k<=maxa;k++)
			f[i][j][k]+=f[i-1][j][k];
for (int i=1;i<=maxa;i++)
	for (int j=1;j<=maxa;j++)
		for (int k=1;k<=maxa;k++)
			f[i][j][k]+=f[i][j-1][k];
for (int i=1;i<=maxa;i++)
	for (int j=1;j<=maxa;j++)
		for (int k=1;k<=maxa;k++)
			f[i][j][k]+=f[i][j][k-1];
// f[i][j][k] is the answer of [1..i][1..j][1..k] 