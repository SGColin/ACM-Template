LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
LL exgcd(LL a,LL b,LL &x,LL &y){
	if (!b) {x=1;y=0;return a;}
	LL r=exgcd(b,a%b,y,x);y-=a/b*x;
	return r;
}
LL Inv(LL A,LL C){
	LL x,y;exgcd(A,C,x,y);
	return (x%C+C)%C;
}
struct Hashmap{
	static const int HA=99991,maxe=46341;
	int E,lnk[HA],nxt[maxe+5];LL to[maxe+5],w[maxe+5];
	int top,stk[maxe+5];
	inline void Add(int x,LL y) {stk[++top]=x;to[++E]=y;w[E]=0;nxt[E]=lnk[x];lnk[x]=E;}
	void clear() {E=0;while (top) lnk[stk[top--]]=0;}
	bool count(LL x){
		int ha=x%HA;
		for (int j=lnk[ha];j;j=nxt[j])
			if (to[j]==x) return true;
		return false;
	}
	LL& operator [] (LL x){
		int ha=x%HA;
		for (int j=lnk[ha];j;j=nxt[j])
			if (to[j]==x) return w[j];
		Add(ha,x);return w[E];
	}
};
LL BSGS(LL A,LL B,LL C){ // A^x=B(mod C)
	static Hashmap f;
	A%=C;B%=C;
	if (!A && B) return B==1?0:-1; // if 0^0=1
	LL m=sqrt(C)+1,pw=1,INV=Inv(A,C),ipw=1,w=1;
	f.clear();
	for (int i=0;i<m;i++){
		LL now=ipw*B%C;
		if (!f.count(now)) f[now]=i;
		pw=pw*A%C;ipw=ipw*INV%C;
	}
	for (int i=0;i<m;i++,w=w*pw%C) if (f.count(w)) return i*m+f[w];
	return -1;
}
LL exBSGS(LL A,LL B,LL C){ // extend A^x=B(mod C)
	static Hashmap f;
	A%=C;B%=C;
	if (!A && B) return B==1?0:-1; // if 0^0=1
	LL pw=1%C;
	for (int i=0;i<30;i++,pw=pw*A%C) if (pw==B) return i;
	LL r,D=1,num=0;
	while ((r=gcd(A,C))>1){
		if (B%r) return -1;num++;
		B/=r;C/=r;D=(D*A/r)%C;
	}
	A%=C;
	LL m=sqrt(C)+1,INV=Inv(A,C),ipw=1;pw=1;
	f.clear();
	for (int i=0;i<m;i++){
		LL now=ipw*B%C;
		if (!f.count(now)) f[now]=i;
		pw=pw*A%C;ipw=ipw*INV%C;
	}
	for (int i=0;i<m;i++,D=D*pw%C) if (f.count(D)) return i*m+f[D]+num;
	return -1;
}