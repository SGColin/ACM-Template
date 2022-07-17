namespace Comb {
    int fac[N], ifac[N];
 
    inline int fpow(int x, int t) {
        int res = 1;
        for (; t; t >>= 1, x = 1ll * x * x % mod)
            if (t & 1) res = 1ll * res * x % mod;
        return res;
    }
 
    inline void init() {
        fac[0] = ifac[0] = 1;
        for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
        ifac[N - 1] = fpow(fac[N - 1], mod - 2);
        for (int i = N - 2; i; --i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
    }
 
    inline int C(int n, int m) {
        if (n < m) return 0;
        return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
    }
}