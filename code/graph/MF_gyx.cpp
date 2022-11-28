inline bool getmin(int &a, int b) {return (a > b ? (a = b, true) : false);}
inline bool getmax(int &a, int b) {return (a < b ? (a = b, true) : false);}
 
// F is the type of flow
template<const int V, const int E, class F, const F flowInf>
struct MF {
 
    int tot = 1, S, T, hd[V], cur[V], dis[V];
    struct edge{int to, nxt; F cap;} e[E << 1];
 
    void clear() {tot = 1; memset(hd, 0, sizeof(hd));}
    void add(int u, int v, F w) {
        e[++tot].nxt = hd[u], hd[u] = tot, e[tot].to = v, e[tot].cap = w;
        e[++tot].nxt = hd[v], hd[v] = tot, e[tot].to = u, e[tot].cap = 0;
    }
    inline bool bfs() {
        static int q[V], qhd, qtl; 
        memcpy(cur, hd, sizeof(hd));
        memset(dis, -1, sizeof(dis));
        q[qhd = qtl = 1] = S; dis[S] = 0;
        while (qhd <= qtl) {
            int u = q[qhd++];
            for (int i = hd[u], v; i; i = e[i].nxt)
                if (dis[v = e[i].to] == -1 && e[i].cap != 0) {
                    dis[v] = dis[u] + 1; q[++qtl] = v;
                }
        }
        return dis[T] != -1;
    }
    F dfs(int u, F rem) {
        if (u == T) return rem;
        F flow = 0;
        for (int i = cur[u], v; i && rem; i = e[i].nxt) {
            cur[u] = i; v = e[i].to;
            F nw = min(rem, e[i].cap);
            if (nw != 0 && dis[v] == dis[u] + 1) {
                int ret = dfs(v, nw);
                flow += ret; rem -= ret; 
                e[i].cap -= ret; e[i ^ 1].cap += ret;
            }
        }
        if (flow == 0) dis[u] = -1;
        return flow;
    }
    F dinic(int source, int sink) {
        S = source; T = sink; F flow = 0;
        while (bfs()) flow += dfs(S, flowInf);
        return flow;
    }
};