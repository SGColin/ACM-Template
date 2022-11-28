int sz[N], mxs[N];
vector<int> e[N];
void dfs(int u, int fa) {
    sz[u] = 1;
    for (auto v : e[u])
        if (v != fa) {
            dfs(v, u); sz[u] += sz[v];
            if (sz[v] > sz[mxs[u]]) mxs[u] = v;
        }
}
inline void upd(int u) {  /*adding information of u into data structures*/}
inline void del(int u) {/*deleting information of u from data structures*/}
void upd(int u, int fa) {upd(u); for (auto v : e[u]) if (v != fa) upd(v, u);}
void del(int u, int fa) {del(u); for (auto v : e[u]) if (v != fa) del(v, u);}
void dsu(int u, int fa) {
    for (auto v : e[u]) if (v != fa && v != mxs[u]) {dsu(v, u); del(v, u);}
    if (mxs[u]) dsu(mxs[u], u);
    for (auto v : e[u]) if (v != fa && v != mxs[u]) upd(v, u);
    upd(u); 
}
// 预处理轻儿子子树部分
vector<int> subtree[N];
void dsu(int u, int fa) {
    for (auto v : e[u])
        if (v != fa && v != mxs[u]) {dsu(v, u); for (auto k : subtree[v]) del(k);}
    if (mxs[u]) dsu(mxs[u], u);
    for (auto v : e[u]) 
        if (v != fa && v != mxs[u]) for (auto k : subtree[v]) add(k);
    add(u);
}
void get_subtree(int u, int fa, int cur) {
    subtree[cur].pb(u);
    for (auto v : e[u]) if (v != fa) get_subtree(v, u, cur);
}
void dsu_tree(int u, int fa) {
    for (auto v : e[u]) if (v != fa && v != mxs[u]) get_subtree(v, u, v);
    for (auto v : e[u]) if (v != fa) dsu_tree(v, u);
}
dfs(1, 1); dsu_tree(1, 1); dsu(1, 1);