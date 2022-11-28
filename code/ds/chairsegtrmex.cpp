#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100000,maxt=1e7;

int n,a[maxn+5],ID[maxn+5],ans;bool ok[maxn+5];
int si,ro[maxn+5],ls[maxt+5],rs[maxt+5],MIN[maxt+5];

inline bool cmp(const int &i,const int &j) {return a[i]<a[j] || a[i]==a[j] && i<j;}
int Build(int L,int R){
	int now=++si;if (L==R) return now; int mid=L+(R-L>>1);
	ls[now]=Build(L,mid);rs[now]=Build(mid+1,R);return now;
}
int Insert(int p,int pos,int k,int l=1,int r=n+1){ // notice the range [1,n+1]
	int now=++si;ls[now]=ls[p];rs[now]=rs[p];MIN[now]=MIN[p];
	if (l==r) {MIN[now]=k;return now;} int mid=l+(r-l>>1);
	if (pos<=mid) ls[now]=Insert(ls[p],pos,k,l,mid); 
	else rs[now]=Insert(rs[p],pos,k,mid+1,r);
	MIN[now]=min(MIN[ls[now]],MIN[rs[now]]); return now;
}
int Mex(int p,int k,int l=1,int r=n+1){
	if (l==r) return l; int mid=l+(r-l>>1);
	if (MIN[ls[p]]<k) return Mex(ls[p],k,l,mid); else return Mex(rs[p],k,mid+1,r);
}
int main(){
	scanf("%d",&n);ro[0]=Build(1,n+1);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),ID[i]=i,ro[i]=Insert(ro[i-1],a[i],i);
	sort(ID+1,ID+1+n,cmp);
	for (int L=1,R;L<=n;L=R+1){
		int now=a[ID[L]];for (R=L+1;R<=n && a[ID[R]]==now;R++);R--;
		if (ID[L]>1 && Mex(ro[ID[L]-1],1)==now) goto OK;
		for (int i=L;i<R;i++) 
			if (ID[i]+1<=ID[i+1]-1 && Mex(ro[ID[i+1]-1],ID[i]+1)==now) goto OK;
		if (ID[R]<n && Mex(ro[n],ID[R]+1)==now) goto OK;
		continue;OK:ok[a[ID[L]]]=true;
	}
	ok[Mex(ro[n],1)]=true;ans=1;while (ok[ans]) ans++;
	printf("%d\n",ans);return 0;
}