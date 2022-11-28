bool vis[N], instack[N];
int idxcnt, idx[N], low[N], top, stk[N], scc, bl[N];
void dfs(int u) {
    low[u] = idx[u] = ++idxcnt;
    instack[stk[++top] = u] = true;
    for (auto v : re[u]) // on reversed graph
        if (!idx[v]) {dfs(v); low[u] = min(low[u], low[v]);} 
        else if (instack[v])  low[u] = min(low[u], idx[v]);
    if (low[u] == idx[u]) { // find a scc with root u
        ++scc;
        do {
            instack[stk[top]] = false;
            nodes[bl[stk[top]] = scc].push_back(stk[top]);
        } while (stk[top--] != u);
    }
}
void tarjan(int n) {
	for (int i = 1; i <= n; ++i) if (!idx[i]) dfs(i);
}