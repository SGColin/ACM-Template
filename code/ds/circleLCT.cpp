#define is_ro(p) (son[fa[p]][0]!=(p) && son[fa[p]][1]!=(p))
#define Son(p) ((p)==son[fa[p]][1])
inline void Pushup(int p){
	MIN[p]=min({MIN[son[p][0]],MIN[son[p][1]],p});
	si[p]=si[son[p][0]]+1+si[son[p][1]];
}
void Rotate(int t){
	int p=fa[t],d=Son(t);son[p][d]=son[t][d^1];son[t][d^1]=p;
	if (!is_ro(p)) son[fa[p]][Son(p)]=t;Pushup(p);Pushup(t);
	if (son[p][d]) fa[son[p][d]]=p;fa[t]=fa[p];fa[p]=t;
}
inline void Addflip(int p) {swap(son[p][0],son[p][1]);flip[p]^=1;}
inline void Addtag(int p,pair<int,int> x) {L[p]=x.fr;R[p]=x.sc;tag[p]=x;}
void Pushdown(int p){
	if (flip[p]) Addflip(son[p][0]),Addflip(son[p][1]),flip[p]^=1;
	if (tag[p].fr) Addtag(son[p][0],tag[p]),Addtag(son[p][1],tag[p]),tag[p]=mp(0,0);
}
void Splay(int p){
	static int top,stk[maxn+5];stk[top=1]=p;
	for (int i=p;!is_ro(i);i=fa[i]) stk[++top]=fa[i];
	while (top) Pushdown(stk[top--]);
	for (int pre=fa[p];!is_ro(p);Rotate(p),pre=fa[p])
		if (!is_ro(pre)) Rotate(Son(p)==Son(pre)?pre:p);
}
void Access(int p) {
	for (int lst=0;p;lst=p,p=fa[p]) Splay(p),son[p][1]=lst,Pushup(p);
}
inline void Makero(int x) {Access(x);Splay(x);Addflip(x);}
inline void Link(int x,int y) {Makero(x);Makero(y);fa[x]=y;}
inline void Cut(int x,int y) {
	Makero(x);Access(y);Splay(x);son[x][1]=fa[y]=0;Pushup(x);
}
//Cover L R of the link between x and y
inline void Cover(int x,int y) {Makero(x);Access(y);Splay(y);Addtag(y,mp(x,y));}
inline pair<int,int> Ask(int x,int y) {
	Makero(x);Access(y);Splay(y);return mp(si[y],MIN[y]);
}
//Lx Rx is the head and tail of circle[x]
void SwapP(int x,int y){ // Swap Px Py
	if (x==y) return;
	Splay(x);Splay(y);
	if (L[x]!=L[y]){
		pair<int,int> X=Ask(L[x],R[x]),Y=Ask(L[y],R[y]);
		//Update Here
		if (x!=R[x] && y!=R[y]){
			Cut(x,p[x]);Cut(y,p[y]);
			Link(x,p[y]);Link(y,p[x]);
			Link(R[y],L[y]);Cover(L[x],R[x]);
		} else if (x==R[x] && y==R[y]){Link(R[x],L[y]); Cover(L[x],R[y]);}
		else if (x==R[x]){Cut(y,p[y]);Link(y,L[x]);Link(R[x],p[y]);Cover(L[y],R[y]);} 
		else {Cut(x,p[x]);Link(x,L[y]);Link(R[y],p[x]);Cover(L[x],R[x]);}
		//Update Here
	} else {
		if (Ask(L[x],x).fr>Ask(L[y],y).fr) swap(x,y);
		pair<int,int> X=Ask(L[x],R[x]);
		//Update Here
		int lx=L[x],rx=R[x];
		if (y!=rx){
			Cut(x,p[x]);Cut(y,p[y]);Link(x,p[y]); 
			Cover(lx,rx);X=Ask(lx,rx);
			//Update Here
			Cover(p[x],y);X=Ask(p[x],y);
			//Update Here
		} else {
			Cut(x,p[x]); 
			Cover(lx,x);X=Ask(lx,x);
			//Update Here
			Cover(p[x],rx);X=Ask(p[x],rx);
			//Update Here
		}
	}
	swap(p[x],p[y]);
}