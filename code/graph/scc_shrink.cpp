int indeg[N], outdeg[N];
vector<int> source, sink;
unordered_map<ll, bool> valid;
inline bool has_edge(int u, int v) {
    ll w = 1000000000ll * u + v;
    return valid[w] ? true : (valid[w] = true, 0); 
}
inline void shrink(int n) {
    valid.clear();
    for (int u = 1; u <= n; ++u) e[u].clear();
    for (int v = 1; v <= n; ++v)
        for (auto u : re[v]) 
            if (bl[u] != bl[v] && !has_edge(bl[u], bl[v])) {
                ++indeg[bl[v]]; ++outdeg[bl[u]]; e[bl[u]].push_back(bl[v]);
            }
    for (int u = 1; u <= scc; ++u) if (!indeg[u]) source.push_back(u); 
    for (int u = 1; u <= scc; ++u) if (!outdeg[u]) sink.push_back(u);
    for (int u = 1; u <= n; ++u) re[u].clear();
    for (int u = 1; u <= scc; ++u) for (auto v : e[u]) re[v].push_back(u);
}