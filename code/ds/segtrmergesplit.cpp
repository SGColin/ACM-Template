int ro[maxn+5];bool vis[maxn+5]; // 0 inc 1 dec
map<int,int> S;map<int,int>::iterator l,r,it; // S[x] is the right endpoint of x

void Update(int p,int k){
	// Global update
}
inline int newnode() {} // Clear
inline void Pushup(int p){
	si[p]=si[ls[p]]+si[rs[p]];
	// Update
}
inline void Addflip(int p) {if (p) swap(ls[p],rs[p]),flip[p]^=1;} // fliptag
void Pushdown(int p) {if (flip[p]) Addflip(ls[p]),Addflip(rs[p]),flip[p]=0;}
void Insert(int &p,int pos,int l=1,int r=n){
	if (!p) p=newnode();
	if (l==r) {si[p]++;return;}
	int mid=l+(r-l>>1);
	Pushdown(p);
	pos<=mid?Insert(ls[p],pos,l,mid):Insert(rs[p],pos,mid+1,r);
	Pushup(p);
}
void SplitR(int &p,int q,int k){ // Split q's last k elements
	if (!p) p=newnode();
	Pushdown(q);
	int now=si[rs[q]];
	if (k>=now){
		rs[p]=rs[q];rs[q]=0;
		if (k-=now) SplitR(ls[p],ls[q],k);
	} else SplitR(rs[p],rs[q],k);
	Pushup(p);Pushup(q);
}
// Split [L,R] from [fr,sc], and sort [L,R] to tp
void Split(int fr,int sc,int L,int R,int tp){
	if (R<sc){
		ro[R+1]=0;SplitR(ro[R+1],ro[fr],sc-R);
		vis[R+1]=vis[fr];
		S[fr]=R;Update(fr,ro[fr]);
		S[R+1]=sc;Update(R+1,ro[R+1]);
	}
	if (L>fr){
		ro[L]=0;SplitR(ro[L],ro[fr],R-L+1);
		vis[L]=vis[fr];
		S[fr]=L-1;Update(fr,ro[fr]);
		S[L]=R;Update(L,ro[L]);
	}
	if (vis[L]!=tp) Addflip(ro[L]),vis[L]=tp,Update(L,ro[L]);
}
void Merge(int &x,int y,int l=1,int r=n){
	if (!y) return;if (!x) {x=y;return;}
	int mid=l+(r-l>>1);
	Pushdown(x);Pushdown(y);
	Merge(ls[x],ls[y],l,mid);Merge(rs[x],rs[y],mid+1,r);
	Pushup(x);
}
void AskLR(int p,int L,int R){ // Ask from L-th to R-th
	if (!p) return;
	if (L==1 && R==si[p]) return AskAnswer(); // Ask answer
	Pushdown(p);
	int now=si[ls[p]];
	if (R<=now) AskLR(ls[p],L,R); else if (L>now) AskLR(rs[p],L-now,R-now);
	else AskLR(ls[p],L,now),AskLR(rs[p],1,R-now);
}

// Sort [L,R] to tp
l=prev(S.upper_bound(L));r=prev(S.upper_bound(R));
int A=l->fr,B=l->sc,C=r->fr,D=r->sc;
if (A==C) Split(A,B,L,R,tp); else{
	Split(A,B,L,B,tp);
	Split(C,D,C,R,tp);
	for (it=S.lower_bound(L+1);it!=S.end() && it->sc<=R;it=S.erase(it)){
		if (vis[it->fr]!=tp) Addflip(ro[it->fr]);
		Merge(ro[L],ro[it->fr]);Update(it->fr,0);
	}
	S[L]=R;Update(L,ro[L]);
}

// Ask [L,R]
l=prev(S.upper_bound(L));r=prev(S.upper_bound(R));
int A=l->fr,B=l->sc,C=r->fr,D=r->sc;
if (l==r) AskLR(ro[A],L-A+1,R-A+1); else {
	AskLR(ro[A],L-A+1,B-A+1);
	if (B+1<=C-1) Ask(B+1,C-1); // Global Ask
	AskLR(ro[C],1,R-C+1);
}