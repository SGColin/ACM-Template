void Solve(int L,int R){ // f*g
    if (L==R) {/*Update here*/ return;}
    int mid=L+(R-L>>1);
    Solve(L,mid);
    int t;for (t=1;t<=R-L;t<<=1);
    for (int i=L;i<=mid;i++) A[i-L]=f[i];for (int i=mid-L+1;i<t;i++) A[i]=0;
    B[0]=0;for (int i=1;i<=R-L;i++) B[i]=g[i];for (int i=R-L+1;i<t;i++) B[i]=0;
    NTT(A,t,1);NTT(B,t,1);
    for (int i=0;i<t;i++) A[i]=MUL(A[i],B[i]);
    NTT(A,t,-1);for (int i=mid+1;i<=R;i++) f[i]=ADD(f[i],A[i-L]);
    Solve(mid+1,R);
}
void Solve(int L,int R){ // f*f
    if (L==R) {f[L]=ADD(f[L],MUL(L-1,f[L-1]));return;}
    int mid=L+(R-L>>1); Solve(L,mid);
    if (R-L<L){
        int t;for (t=1;t<=R-L;t<<=1);
        for (int i=L;i<=mid;i++) A[i-L]=f[i];
        for (int i=mid-L+1;i<t;i++) A[i]=0;
        for (int i=2;i<=R-L;i++) B[i]=MUL(i-1,f[i]);
        B[0]=B[1]=0;for (int i=R-L+1;i<t;i++) B[i]=0;
        NTT(A,t,1);NTT(B,t,1);
        for (int i=0;i<t;i++) A[i]=MUL(A[i],B[i]);NTT(A,t,-1);
        for (int i=mid+1;i<=R;i++) f[i]=ADD(f[i],A[i-L]);
        for (int i=L;i<=mid;i++) A[i-L]=MUL(i-1,f[i]);
        for (int i=mid-L+1;i<t;i++) A[i]=0;
        for (int i=2;i<=R-L;i++) B[i]=f[i];
        B[0]=B[1]=0;for (int i=R-L+1;i<t;i++) B[i]=0;
        NTT(A,t,1);NTT(B,t,1);
        for (int i=0;i<t;i++) A[i]=MUL(A[i],B[i]);NTT(A,t,-1);
        for (int i=mid+1;i<=R;i++) f[i]=ADD(f[i],A[i-L]);
    } else {
        int t;for (t=1;t<=(mid-L<<1);t<<=1);
        for (int i=L;i<=mid;i++) A[i-L]=f[i],B[i-L]=MUL(i-1,f[i]);
        for (int i=mid-L+1;i<t;i++) A[i]=B[i]=0;
        NTT(A,t,1);NTT(B,t,1);
        for (int i=0;i<t;i++) A[i]=MUL(A[i],B[i]);NTT(A,t,-1);
        for (int i=mid+1;i<=R;i++) if (i>=(L<<1)) f[i]=ADD(f[i],A[i-(L<<1)]);
    }
    Solve(mid+1,R);
}