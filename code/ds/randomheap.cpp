int ro[maxn+5],son[maxn+5][2],fa[maxn+5],tag[maxn+5];
int fat[maxn+5];

int getfa(int x) {return x==fat[x]?x:fat[x]=getfa(fat[x]);}
inline void Addtag(int p,int k) {if (!p) return;a[p]+=k;tag[p]+=k;}
inline void Pushdown(int p) {
	if (tag[p]) Addtag(son[p][0],tag[p]),Addtag(son[p][1],tag[p]),tag[p]=0;
}
int Merge(int A,int B){
	if (!A || !B) return A+B;
	if (a[A]<a[B]) swap(A,B);Pushdown(A);
	int d=rand()&1;son[A][d]=Merge(son[A][d],B);
	if (son[A][0]) fa[son[A][0]]=A;if (son[A][1]) fa[son[A][1]]=A;
	return A;
}
#define Son(x) ((x)==son[fa[x]][1])
inline void Swap(int x,int f){
	int d=Son(x);swap(son[x],son[f]);son[x][d]=f;
	if (son[f][0]) fa[son[f][0]]=f;if (son[f][1]) fa[son[f][1]]=f;
	if (son[x][d^1]) fa[son[x][d^1]]=x;
	if (fa[f]) son[fa[f]][Son(f)]=x; else ro[getfa(x)]=x;
	fa[x]=fa[f];fa[f]=x;
}
inline void Add(int x,int v){
	static int top=0,stk[maxn+5];
	for (int i=x;i;i=fa[i]) stk[++top]=i;while (top) Pushdown(stk[top--]);a[x]+=v;
	for (int f=fa[x];f&&a[x]>a[f];f=fa[x]) Swap(x,f);
	int l,r;
	for (l=son[x][0],r=son[x][1];l&&a[x]<a[l]||r&&a[x]<a[r];l=son[x][0],r=son[x][1]){
		if (!l||r&&a[r]>a[l]) l=r;
		Pushdown(l);Swap(l,x);
	}
}