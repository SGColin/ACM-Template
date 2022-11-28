const int maxi= /* size of character set */ ;
int qui[maxn+5][maxi]; // quickly transform
inline int newnode() {pl++;for (int i=0;i<maxi;i++) son[pl][i]=qui[pl][i]=0;return pl;}
void Exback(int l,int i){ // left is l, and now insert a[i]
	int c=a[i];if (i-len[pb]-1<l || a[i-len[pb]-1]!=c) pb=qui[pb][c];
	if (!son[pb][c]){
		int u=newnode(),k=fai[pb];len[u]=len[pb]+2;
		if (a[i-len[k]-1]!=c) k=qui[k][c];k=son[k][c];
		for (int i=0;i<maxi;i++) qui[u][i]=qui[k][i];
		qui[u][a[i-len[k]]]=k;fai[u]=k;son[pb][c]=u;
	}
	pb=son[pb][c];if (len[pb]==i-l+1) pf=pb;
}
void Exfront(int i,int r){ // right is r, and now insert a[i]
	int c=a[i];if (i+len[pf]+1>r || a[i+len[pf]+1]!=c) pf=qui[pf][c];
	if (!son[pf][c]){
		int u=newnode(),k=fai[pf];len[u]=len[pf]+2;
		if (a[i+len[k]+1]!=c) k=qui[k][c];k=son[k][c];
		for (int i=0;i<maxi;i++) qui[u][i]=qui[k][i];
		qui[u][a[i+len[k]]]=k;fai[u]=k;son[pf][c]=u;
	}
	pf=son[pf][c];if (len[pf]==r-i+1) pb=pf;
}
pl=-1;newnode();newnode(); // clear root
fai[0]=fai[1]=1;len[0]=0;len[1]=-1;
for (int i=0;i<maxi;i++) qui[0][i]=1;
pb=pf=0;