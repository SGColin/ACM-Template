#define is_ro(p) (son[fa[p]][0]!=(p) && son[fa[p]][1]!=(p))
#define Son(p) ((p)==son[fa[p]][1])
void Pushup(int p) {si[p]=si[son[p][0]]+1+si[son[p][1]];}
void Rotate(int t){
	int p=fa[t],d=Son(t);son[p][d]=son[t][d^1];son[t][d^1]=p;
	if (!is_ro(p)) son[fa[p]][Son(p)]=t;Pushup(p);Pushup(t);
	if (son[p][d]) fa[son[p][d]]=p;fa[t]=fa[p];fa[p]=t;
}
void Addflip(int p) {swap(son[p][0],son[p][1]);flip[p]^=1;}
void Pushdown(int p) {if (flip[p]) Addflip(son[p][0]),Addflip(son[p][1]),flip[p]^=1;}
void Splay(int p){
	static int top,stk[maxn+5];stk[top=1]=p;
	for (int i=p;!is_ro(i);i=fa[i]) stk[++top]=fa[i];
	while (top) Pushdown(stk[top--]);
	for (int pre=fa[p];!is_ro(p);Rotate(p),pre=fa[p])
		if (!is_ro(pre)) Rotate(Son(p)==Son(pre)?pre:p);
}
void Access(int p) {for (int lst=0;p;lst=p,p=fa[p]) Splay(p),son[p][1]=lst,Pushup(p);}
void Makero(int x) {Access(x);Splay(x);Addflip(x);}
void Link(int x,int y) {Makero(x);Makero(y);fa[x]=y;}
void Cut(int x,int y) {Makero(x);Access(y);Splay(x);son[x][1]=fa[y]=0;Pushup(x);}
int Ask(int x) {Makero(n);Access(x);Splay(x);return si[x];}
int LCA(int x,int p){
	int ans;Access(x);
	for (int lst=0;p;lst=p,p=fa[p]) Splay(p),son[p][1]=lst,Pushup(p),ans=p;
	return ans;
}