const int maxi=size of character set;
inline int newnode() {pl++;for (int i=0;i<maxi;i++) son[pl][i]=0;return pl;}
// normal
int Extend(int p,int c,int id){
	int np=newnode();MAX[np]=MAX[p]+1;ID[id]=np;
	while (p && !son[p][c]) son[p][c]=np,p=fai[p];
	if (!p) {fai[np]=ro;return np;}
	int q=son[p][c];if (MAX[p]+1==MAX[q]) {fai[np]=q;return np;}
	int nq=newnode();MAX[nq]=MAX[p]+1;
	for (int i=0;i<maxi;i++) son[nq][i]=son[q][i];
	fai[nq]=fai[q];fai[q]=fai[np]=nq;
	while (p && son[p][c]==q) son[p][c]=nq,p=fai[p];
	return np;
}
// generalized
int Extend(int p,int c,int ID){
	if (son[p][c]){
		int q=son[p][c];if (MAX[p]+1==MAX[q]) return q;
		int nq=newnode();MAX[nq]=MAX[p]+1;
		for (int i=0;i<maxi;i++) son[nq][i]=son[q][i];
		fai[nq]=fai[q];fai[q]=nq;
		while (p && son[p][c]==q) son[p][c]=nq,p=fai[p];
		return nq;
	} else {
		int np=newnode();MAX[np]=MAX[p]+1;
		while (p && !son[p][c]) son[p][c]=np,p=fai[p];
		if (!p) {fai[np]=ro;return np;}
		int q=son[p][c];if (MAX[p]+1==MAX[q]) {fai[np]=q;return np;}
		int nq=newnode();MAX[nq]=MAX[p]+1;
		for (int i=0;i<maxi;i++) son[nq][i]=son[q][i];
		fai[nq]=fai[q];fai[q]=fai[np]=nq;
		while (p && son[p][c]==q) son[p][c]=nq,p=fai[p];
		return np;
	}
}