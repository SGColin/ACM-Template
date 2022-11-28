void Manacher(char *a,int n){
	int pos=0,R=0;
	for (int i=1;i<=n;i++){
		if (i<R) p[i]=min(p[(pos<<1)-i],R-i); else p[i]=1;
		while (1<=i-p[i] && i+p[i]<=n && a[i-p[i]]==a[i+p[i]]) p[i]++;
		if (i+p[i]>R) pos=i,R=i+p[i];
	}
}

for (int i=1;i<=n;i++) a[(i<<1)-1]=s[i],a[i<<1]='%';
Manacher(a,(n<<1)-1);