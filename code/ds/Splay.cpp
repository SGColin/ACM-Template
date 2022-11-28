struct SplayTree{
	int pl,ro,son[maxt+5][2],fa[maxt+5],si[maxt+5];bool flip[maxt+5];
	int cmp(int p,int &k){
		if (k<=si[son[p][0]]) return 0;
		if (k==si[son[p][0]]+1) return -1;
		k-=si[son[p][0]]+1;return 1;
	}
	void Pushup(int p) {si[p]=si[son[p][0]]+1+si[son[p][1]];}
	int newnode() {pl++;son[pl][0]=son[pl][1]=fa[pl]=flip[pl]=0;si[pl]=1;return pl;}
	int Build(int L,int R,int pre=0){
		if (L>R) return 0;
		int mid=L+(R-L>>1),now=newnode();
		son[now][0]=BuildA(L,mid-1,now);son[now][1]=BuildA(mid+1,R,now);
		fa[now]=pre;Pushup(now);return now;
	}
	void Clear(int n) {pl=0;ro=Build(0,n+1);} // Build 0~n+1
	void Rotate(int &p,int d){
		int t=son[p][d];son[p][d]=son[t][d^1];son[t][d^1]=p;Pushup(p);Pushup(t);
		if (son[p][d]) fa[son[p][d]]=p;fa[t]=fa[p];fa[p]=t;p=t;
	}
	void Addflip(int p) {if (!p) return;swap(son[p][0],son[p][1]);flip[p]^=1;}
	void Pushdown(int p) {if(flip[p])Addflip(son[p][0]),Addflip(son[p][1]),flip[p]^=1;}
	void Splay(int &p,int k){
		int d=cmp(p,k);Pushdown(p);if (d<0) return;
		int &t=son[p][d],f=cmp(t,k);Pushdown(t);
		if (~f) Splay(son[t][f],k),d==f?Rotate(p,d):Rotate(t,f);Rotate(p,d);
	}
	int Askkth(int p,int k){
		int d=cmp(p,k);Pushdown(p);
		return ~d?Askkth(son[p][d],k):p;
	}
	int Askrk(int p){
		static int top,stk[maxt+5];
		top=0;for (int i=p,f=fa[i];i!=ro;i=f,f=fa[i]) stk[++top]=fa[i];
		while (top) Pushdown(stk[top]),top--;
		int rk=si[son[p][0]]+1;
		for (int f=fa[p];p!=ro;p=f,f=fa[p])
			if (p==son[f][1]) rk+=si[son[f][0]]+1;
		Splay(ro,rk);return rk;
	}
	int getseg(int L,int R){
		L--;R++;Splay(ro,L);cmp(ro,R);Splay(son[ro][1],R);
		return son[son[ro][1]][0];
	}
	int Insert(int x){
		int now=newnode();getseg(x,x-1);
		son[son[ro][1]][0]=now;fa[now]=son[ro][1];
		Pushup(son[ro][1]);Pushup(ro);return now;
	}
}tr;
/*use hint
build [0,n+1]: tr.Clear(n);
segment [L,R]: L++;R++;tr.getseg(L,R);
*/