inline int Det() {
	assert(n == m);
	bool fl = 0;
	rep(i, 1, n) { // Mod a Prime!!
		int nw = i;
		rep(j, i, n) if (a[j][i]) {nw = j; break;}
		if (a[nw][i] == 0) return 0;
		if (nw != i) {swap(a[nw], a[i]); fl ^= 1;}
		int inv = ::fpow(a[i][i], mod - 2);
		rep(j, i + 1, n) 
			if (a[j][i]) {
				ll cof = mod - 1ll * inv * a[j][i] % mod;
				rep(k, i, n) a[j][k] = (a[j][k] + cof * a[i][k]) % mod;
			}
	}
	rep(i, 1, n) { // Mod a simple number!!
		int nw = i;
		rep(j, i, n) if (a[j][i] && (!a[nw][i] || a[nw][i] > a[j][i])) nw = j;
		if (a[nw][i] == 0) return 0;
		if (nw != i) {swap(a[nw], a[i]); fl ^= 1;}
		rep(j, i + 1, n)
			while (a[j][i]) { // 辗转相除，复杂度还是 O(n^3) 的
				if (a[i][i] > a[j][i]) {swap(a[j], a[i]); fl ^= 1;}
				int cof = mod - a[j][i] / a[i][i];
				rep(k, i, n) a[j][k] = (a[j][k] + 1ll * cof * a[i][k]) % mod;
			}
	}
	int res = 1;
	for (int i = 1; i <= n; ++i) res = 1ll * res * a[i][i] % mod;
	return fl ? (mod - res) % mod : res;
}