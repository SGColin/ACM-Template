struct SAM{
	int p,pl,ro,son[maxt+5][maxi],fai[maxt+5],MAX[maxt+5],vis[maxt+5];
	int to[maxt+5][2],fa[maxt+5],si[maxt+5][2];bool flip[maxt+5];
	#define is_ro(p) ((p)!=to[fa[p]][0] && (p)!=to[fa[p]][1])
	#define Son(p) ((p)==to[fa[p]][1])
	inline void Pushup(int p) {
		si[p][1]=si[to[p][0]][1]+si[to[p][1]][1]+si[p][0]+vis[p];
	}
	inline void Rotate(int t){
		int p=fa[t],d=Son(t);to[p][d]=to[t][d^1];to[t][d^1]=p;
		Pushup(p);Pushup(t);if (!is_ro(p)) to[fa[p]][Son(p)]=t;
		if (to[p][d]) fa[to[p][d]]=p;fa[t]=fa[p];fa[p]=t;
	}
	inline void Addflip(int p) {swap(to[p][0],to[p][1]);flip[p]^=1;}
	inline void Pushdown(int p) {
		if (flip[p]) flip[p]^=1,Addflip(to[p][0]),Addflip(to[p][1]);
	}
	inline void Splay(int p){
		static int top,stk[maxt+5];stk[top=1]=p;
		for (int i=p;!is_ro(i);i=fa[i]) stk[++top]=fa[i];
		while (top) Pushdown(stk[top--]);
		for (int pre=fa[p];!is_ro(p);Rotate(p),pre=fa[p])
			if (!is_ro(pre)) Rotate(Son(p)==Son(pre)?pre:p);
	}
	inline void Access(int p){
		for (int lst=0;p;Pushup(p),lst=p,p=fa[p])
			Splay(p),si[p][0]+=si[to[p][1]][1]-si[lst][1],to[p][1]=lst;
	}
	inline void Makero(int x) {Access(x);Splay(x);Addflip(x);}
	inline void Link(int x,int y) {
		Makero(x);Makero(y);fa[x]=y;si[y][0]+=si[x][1];Pushup(y);
	}
	inline void Cut(int x,int y) {
		Makero(x);Access(y);Splay(y);fa[x]=to[y][0]=0;Pushup(y);
	}
	int newnode(){
		pl++;for (int i=0;i<maxi;i++) son[pl][i]=0;vis[pl]=0;
		to[pl][0]=to[pl][1]=fa[pl]=si[pl][0]=si[pl][1]=flip[pl]=0;
		return pl;
	}
	void clear() {pl=0;ro=newnode();p=ro;}
	void Extend(int c){
		int np=newnode();MAX[np]=MAX[p]+1;vis[np]=1;Pushup(np);
		while (p && !son[p][c]) son[p][c]=np,p=fai[p];
		if (!p) {Link(np,ro);fai[np]=ro;p=np;return;}
		int q=son[p][c];if (MAX[p]+1==MAX[q]) {Link(np,q);fai[np]=q;p=np;return;}
		int nq=newnode();MAX[nq]=MAX[p]+1;
		for (int i=0;i<maxi;i++) son[nq][i]=son[q][i];
		Cut(q,fai[q]);Link(nq,fai[q]);Link(q,nq);Link(np,nq);
		fai[nq]=fai[q];fai[q]=fai[np]=nq;
		while (p && son[p][c]==q) son[p][c]=nq,p=fai[p];
		p=np;return;
	}
};
int Sum(SAM &tr,char *s){
	int p=tr.ro;for (int i=1;s[i];i++) p=tr.son[p][s[i]-'a'];
	if (!p) return 0;
	tr.Makero(tr.ro);tr.Access(p);tr.Splay(p);
	return tr.si[p][0]+tr.vis[p];
}