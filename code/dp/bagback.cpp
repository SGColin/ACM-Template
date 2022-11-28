for (int i=a[x];i<=maxv;i++) g[i]=ADD(g[i],MOD-g[i-a[x]]); // limited
for (int i=maxv;i>=a[i];i--) g[i]=ADD(g[i],MOD-g[i-a[x]]); // unlimited