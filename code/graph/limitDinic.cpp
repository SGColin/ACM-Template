inline void Add(int x,int y,int L,int R){ // x->y limit [L,R]
	to[++E]=y;e[E]=R-L;nxt[E]=lnk[x];lnk[x]=E;
	to[++E]=x;e[E]=0;nxt[E]=lnk[y];lnk[y]=E;
	num[x]-=L;num[y]+=L;
}

S=0;T=maxn+1;SS=T+1;TT=SS+1;ful=0;
E=1;for (int i=S;i<=TT;i++) lnk[i]=num[i]=0;
/* Build graph */

/* Legal flow */
for (int i=S;i<=T;i++)
	if (num[i]>0) Add(SS,i,0,num[i]),ful+=num[i]; else
	if (num[i]<0) Add(i,TT,0,-num[i]);
Add(T,S,0,2e9);
int MF;
if (Dinic(SS,TT)==ful) MF=e[E]; // flow from S to T
else puts("illegal");

/* Max flow */
for (int j=lnk[SS];j;j=nxt[j]) e[j]=e[j^1]=0;
for (int j=lnk[TT];j;j=nxt[j]) e[j]=e[j^1]=0;
e[E]=e[E^1]=0;
MF+=Dinic(S,T);