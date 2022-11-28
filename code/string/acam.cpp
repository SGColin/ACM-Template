void getfai(){
    int Head=0,Tail=0;
    for (int i=0,u;i<26;i++)
        if (u=son[0][i]) fai[u]=0,que[++Tail]=u; else son[0][i]=0;
    while (Head!=Tail)
        for (int x=que[++Head],i=0,u;i<26;i++)
            if (u=son[x][i]) fai[u]=son[fai[x]][i],que[++Tail]=u;
            else son[x][i]=son[fai[x]][i];
}