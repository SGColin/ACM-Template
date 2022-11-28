void Addedge(int x,int y,int z,int c){
	if (c>=0) Add(x,y,z,c); else {
		num[x]-=z;num[y]+=z;ansC+=z*c; // x->y full flow
		Add(y,x,z,-c);
	}
}

/* Build graph */

/* Legal flow */
for (int i=1;i<=n;i++)
	if (num[i]>0) Add(SS,i,num[i],0); else
	if (num[i]<0) Add(i,TT,-num[i],0);
Add(T,S,2e9,0);
int MF,MC;MCMF(SS,TT,MF,MC);
ansF+=e[E];ansC+=MC;

/* Max flow */
for (int j=lnk[SS];j;j=nxt[j]) e[j]=e[j^1]=0;
for (int j=lnk[TT];j;j=nxt[j]) e[j]=e[j^1]=0;
e[E]=e[E^1]=0;
MCMF(S,T,MF,MC);
ansF+=MF;ansC+=MC;