bool vis[N];
int n, m, scc, bl[N];
vector<int> e[N], re[N], nodes[N], order;
void add(int u, int v) {e[u].pb(v); re[v].pb(u);}
void dfs1(int u) {
    vis[u] = 1;
    for (auto v : e[u]) if (!vis[v]) dfs1(v);
    order.pb(u);
}
void dfs2(int u) {
    nodes[bl[u] = scc].pb(u);
    for (auto v : re[u]) if (!bl[v]) dfs2(v);
}
void kosaraju(int n) {
    for (int u = 1; u <= n; ++u) if (!vis[u]) dfs1(u);
    reverse(order.begin(), order.end());
    for (auto u : order) if (!bl[u]) {++scc; dfs2(u);}
}
// ===== shrink nodes =====
int indeg[N], outdeg[N];
vector<int> source, sink;
unordered_map<ll, bool> valid;
inline bool has_edge(int u, int v) {
    ll w = 1000000000ll * u + v;
    if (valid[w]) return 1; 
    valid[w] = 1; return 0;
}
inline void shrink(int n) {
    valid.clear();
    for (int u = 1; u <= n; ++u) e[u].clear();
    for (int v = 1; v <= n; ++v)
        for (auto u : re[v]) 
            if (bl[u] != bl[v] && !has_edge(bl[u], bl[v])) {
                ++indeg[bl[v]]; ++outdeg[bl[u]]; e[bl[u]].pb(bl[v]);
            }
    for (int u = 1; u <= scc; ++u) if (!indeg[u]) source.pb(u); 
    for (int u = 1; u <= scc; ++u) if (!outdeg[u]) sink.pb(u);
    for (int u = 1; u <= n; ++u) re[u].clear();
    for (int u = 1; u <= scc; ++u) for (auto v : e[u]) re[v].pb(u);
}