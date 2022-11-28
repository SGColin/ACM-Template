template <const int V, const int inf = 1000000000>
struct Hopcroft_Karp {
    bool vis[V];
    vector<int> e[V];
    int nl, nr, ml[V], mr[V], dl[V], dr[V]; // m for match, d for distance
    inline bool bfs() {
        static int q[V], hd, tl, dT; hd = 1; tl = 0; dT = inf;
        memset(dl, -1, sizeof(int) * (nl + 1)); 
        memset(dr, -1, sizeof(int) * (nr + 1));
        for (int i = 1; i <= nl; ++i) if (!ml[i]) {dl[i] = 0; q[++tl] = i;}
        for (int u; hd <= tl;) {
            if (dl[u = q[hd++]] >= dT) break;
            for (auto v : e[u])
                if (dr[v] == -1) {
                    dr[v] = dl[u] + 1;
                    if (!mr[v]) getmin(dT, dr[v] + 1);
                    else {dl[mr[v]] = dr[v] + 1; q[++tl] = mr[v];}
                }
        }
        return dT != inf;
    }
    bool dfs(int u) {
        for (auto v : e[u]) {
            if (vis[v] || dl[u] + 1 != dr[v]) continue;
            vis[v] = true;
            if (!mr[v] || dfs(mr[v])) {mr[v] = u; ml[u] = v; return true;}
        }
        return false;
    }
    inline void add(int u, int v) {e[u].push_back(v);}
    inline int max_matching() {
        int ans = 0;
        while(bfs()) {
            memset(vis, 0, sizeof(bool) * (nr + 1));
            for (int i = 1; i <= nl; ++i) if (!ml[i]) ans += dfs(i);
        }
        return ans;
    }
    bool visl[V], visr[V], anti[V];
    void addtag(int u) {
        visl[u] = true;
        for (auto v : e[u]) if (!visr[v]){visr[v] = true; addtag(mr[v]);}
    }
    void construct() {
        for (int i = 1; i <= nl; ++i) if (!ml[i]) addtag(i);
        // vertex cover:    visl[i] = false || visr[i] = true
        // independent set: visl[i] = true  || visr[i] = false
        // antichain:       visl[i] = true  && visr[i] = false
    }
};