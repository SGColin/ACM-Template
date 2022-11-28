
// F is the type of flow
// C is the type of cost
template<const int V, const int E, class F, class C, const F flowInf>
struct MCMF {

    int tot = 1, S, T, hd[V];
    struct edge{int nxt, to; F cap; C cst;} e[E << 1];

    void clear() {tot = 1; memset(hd, 0, sizeof(hd));}

    void add(int u, int v, F cap, C cst) {
        e[++tot] = {hd[u], v, cap, cst}; hd[u] = tot;
        e[++tot] = {hd[v], u, 0,  -cst}; hd[v] = tot;
    }

    int inid[V]; F fl[V]; C dis[V];
    
    inline bool spfa() {
        static queue<int> q;
        static bool inq[V];
        memset(inq, 0, sizeof(inq));
        memset(dis, 0x3f, sizeof(dis));
        C cstInf = dis[0];
        
        q.push(S); dis[S] = 0; fl[S] = flowInf;
        while (!q.empty()) {
            int u = q.front();
            q.pop(); inq[u] = false;
            for (int i = hd[u], v; i; i = e[i].nxt)
                if (e[i].cap != 0 && getmin(dis[v = e[i].to], dis[u] + e[i].cst)) {
                    inid[v] = i;
                    fl[v] = min(e[i].cap, fl[u]);
                    if (!inq[v]) {inq[v] = true; q.push(v);}
                }
        }
        return dis[T] < cstInf;
    }

    pair<F, C> EK(int source, int sink) {
        S = source; T = sink; 
        F flow = 0; C cost = 0;
        while (spfa()) {
            flow += fl[T];
            cost += dis[T] * fl[T];
            for (int u = T; u != S; u = e[inid[u] ^ 1].to)
                e[inid[u]].cap -= fl[T], e[inid[u] ^ 1].cap += fl[T]; 
        }
        return make_pair(flow, cost);
    }
};