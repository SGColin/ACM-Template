int Extend(int p,char *s,int i){
	while (s[i]!=s[i-len[p]-1]) p=fai[p];
	if (!son[p][s[i]-'a']){
		int u=newnode(),k=fai[p];len[u]=len[p]+2;
		while (s[i]!=s[i-len[k]-1]) k=fai[k];
		fai[u]=son[k][s[i]-'a'];son[p][s[i]-'a']=u;
		dif[u]=len[u]-len[fai[u]];
		anc[u]=(dif[u]==dif[fai[u]]?anc[fai[u]]:fai[u]);
	}
	p=son[p][s[i]-'a'];
	return p;
}
p=Extend(p,s,i);
for (int x=p;x>1;x=anc[x]){
	sum[x]=f[i-(len[anc[x]]+dif[x])];
	if (dif[x]==dif[fai[x]]) sum[x]=ADD(sum[x],sum[fai[x]]);
	f[i]=ADD(f[i],sum[x]);
}