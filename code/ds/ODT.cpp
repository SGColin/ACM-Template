struct node{
	int L,R,c;
	node(int l=0,int r=0,int w=0) {L=l;R=r;c=w;}
	bool operator < (const node &a) const {return L<a.L;}
};
typedef set<node>::iterator SI;
set<node> S;SI it,l,r;

inline SI Node(int x) {return prev(S.upper_bound(node(x,1e9)));}
SI Split(int x){ // split [L,R] to [L,x-1] and [x,R]
	if (x>n) return S.end();
	it=Node(x);if (it->L==x) return it;
	int L=it->L,R=it->R,c=it->c;
	S.erase(it);S.insert(node(L,x-1,c));
	return S.insert(node(x,R,c)).first;
}
void Assign(int L,int R,int c){ // merge [L,R] and change value to c
	r=Split(R+1);l=Split(L);
	for (it=l;it!=S.end() && it->R<=R;it=S.erase(it))
		Insert(ro,it->L,it->R,tag[it->c]-tag[c]);
	S.insert(node(L,R,c));
}