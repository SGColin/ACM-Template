#define val(j,i) (f[j]+Sum((j)+1,(i))) // DP transfer

Head=1;Tail=0;
p[++Tail]=0;l[Tail]=1;r[Tail]=n;
for (int i=1;i<=n;i++){
	f[i]=val(p[Head],i);
	int lst=-1;
	while (Head<=Tail)
		if (val(p[Tail],l[Tail])>val(i,l[Tail])) lst=l[Tail--]; else {
			int L=l[Tail],R=r[Tail];
			for (int mid=L+(R-L>>1);L<=R;mid=L+(R-L>>1))
				val(p[Tail],mid)>val(i,mid)?R=mid-1:L=mid+1;
			if (L<=r[Tail]) lst=L,r[Tail]=L-1;
			break;
		}
	if (~lst) p[++Tail]=i,l[Tail]=lst,r[Tail]=n;
	if (Head<=Tail) {l[Head]++;if (l[Head]>r[Head]) Head++;}
}