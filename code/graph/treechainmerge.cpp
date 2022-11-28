sort(pos+1,pos+1+pos[0],cmp);Add(lt[pos[1]],1);
for (int i=2;i<=pos[0];i++) Add(lt[pos[i]],1),Add(lt[LCA(pos[i-1],pos[i])],-1);