bool vis[N];
int scc, bl[N];
vector<int> e[N], re[N], nodes[N], order;
void add(int u, int v) {e[u].push_back(v); re[v].push_back(u);}
void dfs1(int u) {
    vis[u] = 1;
    for (auto v : e[u]) if (!vis[v]) dfs1(v);
    order.push_back(u);
}
void dfs2(int u) {
    nodes[bl[u] = scc].push_back(u);
    for (auto v : re[u]) if (!bl[v]) dfs2(v);
}
void kosaraju(int n) {
    for (int u = 1; u <= n; ++u) if (!vis[u]) dfs1(u);
    reverse(order.begin(), order.end());
    for (auto u : order) if (!bl[u]) {++scc; dfs2(u);}
}