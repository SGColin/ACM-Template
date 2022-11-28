#define fa(p) (B.getfa(fa[p]))
#define is_ro(p) ((p)!=son[fa(p)][0] && (p)!=son[fa(p)][1])
#define Son(p) ((p)==son[fa(p)][1])
inline void Pushup(int p) {sum[p]=sum[son[p][0]]+val[p]+sum[son[p][1]];}
inline void Rotate(int t){
	int p=fa(t),d=Son(t);son[p][d]=son[t][d^1];son[t][d^1]=p;
	Pushup(p);Pushup(t);if (!is_ro(p)) son[fa(p)][Son(p)]=t;
	if (son[p][d]) fa[son[p][d]]=p;fa[t]=fa(p);fa[p]=t;
}
inline void Addflip(int p) {swap(son[p][0],son[p][1]);flip[p]^=1;}
inline void Pushdown(int p) {
	if (flip[p]) flip[p]^=1,Addflip(son[p][0]),Addflip(son[p][1]);
}
inline void Splay(int p){
	static int top,stk[maxn+5];stk[top=1]=p;
	for (int i=p;!is_ro(i);i=fa(i)) stk[++top]=fa(i);
	while (top) Pushdown(stk[top--]);
	for (int pre=fa(p);!is_ro(p);Rotate(p),pre=fa(p))
		if (!is_ro(pre)) Rotate(Son(p)==Son(pre)?pre:p);
}
inline void Access(int p) {
	for (int lst=0;p;lst=p,p=fa(p)) Splay(p),son[p][1]=lst,Pushup(p);
}
inline void Makero(int x) {Access(x);Splay(x);Addflip(x);}
void DFS(int x,int y){
	if (son[x][0]) val[y]+=val[son[x][0]],DFS(son[x][0],y);
	if (son[x][1]) val[y]+=val[son[x][1]],DFS(son[x][1],y);
	B.fat[x]=y;son[x][0]=son[x][1]=0; // B is LCT dsu
}
inline void Link(int x,int y){
	int fx=A.getfa(x),fy=A.getfa(y); // A is global dsu
	if (fx!=fy) {Makero(x);fa[x]=y;A.fat[fx]=fy;return;}
	Makero(x);Access(y);Splay(y);DFS(y,y);Pushup(y);
}