int mnd[N], mncnt[N], mnpw[N], prm[N], phi[N] = {0, 1};
for (int i = 2; i < N; ++i) {
    if (!mind[i]) {
        prm[++prm[0]] = mnd[i] = mnpw[i] = i; mncnt[i] = 1;  
        phi[i] = i - 1; // cntd[i] = 2; // sumd[i] = 1 + i;  
    }
    for (int j = 1, p = prm[1], n; j <= prm[0]; p = prm[++j]) {
        if ((n = i * p) > N) break;
        if (p == mind[i]) {
            mind[n] = p;
            pw[n] = pw[i] * p; 
            cnt[n] = cnt[i] + 1;
            if (i == pw[i]) phi[n] = phi[i] * p; 
                            // cntd[n] = cnt[n] + 1; 
                            // sumd[n] = (pw[n] * p - 1) / (p - 1);
            else phi[n] = phi[i / pw[i]] * phi[pw[i] * p];
            break;
        }
        mnd[n] = pw[n] = p; cnt[n] = 1; 
        phi[n] = phi[i] * phi[p];
    }
}