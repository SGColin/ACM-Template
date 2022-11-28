#define is_ro(p) ((p)!=son[fa[p]][0] && (p)!=son[fa[p]][1])
#define Son(p) ((p)==son[fa[p]][1])
inline void Pushup(int p) {si[p][1]=si[son[p][0]][1]+si[son[p][1]][1]+si[p][0]+1;}
inline void Rotate(int t){
	int p=fa[t],d=Son(t);son[p][d]=son[t][d^1];son[t][d^1]=p;
	Pushup(p);Pushup(t);if (!is_ro(p)) son[fa[p]][Son(p)]=t;
	if (son[p][d]) fa[son[p][d]]=p;fa[t]=fa[p];fa[p]=t;
}
inline void Addflip(int p) {swap(son[p][0],son[p][1]);flip[p]^=1;}
inline void Pushdown(int p) {
	if (flip[p]) flip[p]^=1,Addflip(son[p][0]),Addflip(son[p][1]);
}
inline void Splay(int p){
	static int top,stk[maxn+5];stk[top=1]=p;
	for (int i=p;!is_ro(i);i=fa[i]) stk[++top]=fa[i];
	while (top) Pushdown(stk[top--]);
	for (int pre=fa[p];!is_ro(p);Rotate(p),pre=fa[p])
		if (!is_ro(pre)) Rotate(Son(p)==Son(pre)?pre:p);
}
inline void Access(int p){
	for (int lst=0;p;Pushup(p),lst=p,p=fa[p]) // change virtual son
		Splay(p),si[p][0]+=si[son[p][1]][1]-si[lst][1],son[p][1]=lst;
}
inline void Makero(int x) {Access(x);Splay(x);Addflip(x);}

// add virtual son
inline void Link(int x,int y) {
	Makero(x);Makero(y);fa[x]=y;si[y][0]+=si[x][1];Pushup(y);
}
void Split(int x,int y) {Makero(x);Access(y);Splay(x);}
int Askg(int x){
	int lim=si[x][1]>>1,suml=0,sumr=0,g=1e9;
	for (int ls=son[x][0],rs=son[x][1];x;ls=son[x][0],rs=son[x][1]){
		Pushdown(x);
		int nowl=suml+si[ls][1],nowr=sumr+si[rs][1];
		if (nowl<=lim && nowr<=lim) g=min(g,x);
		if (nowl<nowr) suml+=si[x][0]+si[ls][1]+1,x=rs;
		else sumr+=si[x][0]+si[rs][1]+1,x=ls;
	}
	Splay(g);
	return g;
}
/*use hint
initial: si[x][1]=1,si[x][0]=0
update center of gravity
fat[x] is the center of gravity in the x's tree
*/
int gx=getfa(x),gy=getfa(y);
Split(gx,gy);
fat[gx]=fat[gy]=fat[g]=g;