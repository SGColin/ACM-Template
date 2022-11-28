int n, m, a[N][N];
Matrix(int _n = N - 1, int _m = N - 1, bool I = false) : n(_n), m(_m) {
	memset(a, 0, sizeof(a)); if (I) rep(i, 1, n) a[i][i] = 1;
}
inline Matrix operator * (const Matrix &obj) const { // assert(m == obj.n);
	Matrix res(n, obj.m);
	rep(i, 1, n) rep(k, 1, m)
		if (a[i][k] != 0) rep(j, 1, obj.m)
			res.a[i][j] = (res.a[i][j] + 1ll * a[i][k] * obj.a[k][j]) % mod;
	return res;
}
inline Matrix fpow(ll t) const {
	Matrix res(n, n, true), tmp = *this;
	for (; t; t >>= 1, tmp = tmp * tmp) if (t & 1) res = res * tmp;
	return res;
}
inline pair<bool, Matrix> Inv() { // assert(n == m);
	Matrix res(n, n, true);
	rep(i, 1, n) { 
		int nw = i;
		rep(j, i, n) if (a[j][i]) {nw = j; break;}
		if (a[nw][i] == 0) return make_pair(false, res);
		if (nw != i) {swap(a[nw], a[i]); swap(res.a[nw], res.a[i]);}
		int inv = ::fpow(a[i][i], mod - 2);
		rep (k, 1, n) {
			a[i][k] = 1ll * a[i][k] * inv % mod; 
			res.a[i][k] = 1ll * res.a[i][k] * inv % mod;
		}
		rep(j, 1, n) if (j != i && a[j][i]) {
			ll cof = mod - a[j][i];
			rep(k, i, n) a[j][k] = (a[j][k] + cof * a[i][k]) % mod;
			rep(k, 1, n) res.a[j][k] = (res.a[j][k] + cof * res.a[i][k]) % mod;
		}
	}
	return make_pair(true, res);
}