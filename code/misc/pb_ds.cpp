#include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
typedef __gnu_pbds::priority_queue<pair<int,int>,
									greater< pair<int,int> >,pairing_heap_tag> Heap;

Heap que;Heap::point_iterator it[maxn+5];bool vis[maxn+5];

inline void Dij(int S){ // n point, start from s
	while (!que.empty()) que.pop();
	for (int i=1;i<=n;i++) it[i]=0,vis[i]=false;
	for (int i=1;i<=n;i++) dis[i]=2e9;
	dis[S]=0;it[S]=que.push(mp(0,S));vis[S]=true;
	while (!que.empty()){
		int x=que.top().sc;que.pop();vis[x]=false;
		for (int j=lnk[0][x];j;j=nxt[j])
			if (dis[x]+w[j]<dis[son[j]]){
				dis[son[j]]=dis[x]+w[j];
				if (vis[son[j]]) que.modify(it[son[j]],mp(dis[son[j]],son[j]));
				else it[son[j]]=que.push(mp(dis[son[j]],son[j])),vis[son[j]]=true;
			}
	}
}