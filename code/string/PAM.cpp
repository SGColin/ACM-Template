const int maxi= /* size of character set */ ;
inline int newnode() {pl++;for (int i=0;i<maxi;i++) son[pl][i]=0;return pl;}
void Extend(char *s,int i){
	while (s[i]!=s[i-len[p]-1]) p=fai[p];
	if (!son[p][s[i]-'a']){
		int u=newnode(),k=fai[p];len[u]=len[p]+2;
		while (s[i]!=s[i-len[k]-1]) k=fai[k];
		fai[u]=son[k][s[i]-'a'];son[p][s[i]-'a']=u;
	}
	p=son[p][s[i]-'a'];num[p]++;
	ID[i]=p; // p is the node of position i
}

pl=-1;newnode();newnode(); // clear root
fai[0]=fai[1]=1;len[0]=0;len[1]=-1;
p=0;
// num[i] is the number of the palindrome of node i
for (int i=si;i>1;i--) num[fai[i]]+=num[i];