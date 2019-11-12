#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define INF 0x7f7f7f7f7f
struct Graph{
	int n, m, s, t;
	struct Edge{
		int to, cap, flow, next;
	};
	std::vector<Edge> G[1400];
	bool vis[1400];
	int d[1400];
	int cur[1400];
	
	void addEdge(int from, int to, int cap){
		G[from].push_back((Edge){to, cap, 0, G[to].size()});
		G[to].push_back((Edge){from, 0, 0, G[from].size()-1}); 
	} 
	bool BFS() {
		memset(vis, 0, sizeof(vis));
		std::queue<int> q;
		q.push(s);
		d[s] = 0;
		vis[s] = 1;
		while(!q.empty()){
			int x = q.front(); q.pop();
			for(int i = 0; i < G[x].size(); i++){
				Edge& e = G[x][i];
				if(!vis[e.to] && e.cap > e.flow){
					vis[e.to] = 1;
					d[e.to] = d[x] + 1;
					q.push(e.to); 
				}
			}
		}
		return vis[t];
	}
	long long DFS(int x, long long int a) {
		if(x == t || a == 0) return a;
		int flow = 0, f;
		for(int i = cur[x]; i < G[x].size(); i++){
			Edge& e = G[x][i];
			if(d[x]+1 == d[e.to] && (f = DFS(e.to, std::min(a, (long long)e.cap-e.flow))) > 0){
				e.flow += f;
				G[e.to][e.next].flow -= f;
				flow += f;
				a -= f;
				if(a == 0) break;
			}
		}
		return flow;
	}
	
	int Maxflow(){
		int flow = 0;
		while(BFS()){
			memset(cur, 0, sizeof(cur));
			flow += DFS(s, INF);
		}
		return flow;
	}
};
Graph G;
int x, y, c;
int main(){
	scanf("%d%d%d%d", &G.n, &G.m, &G.s, &G.t);
	for(int i = 0; i < G.m; i++){
		scanf("%d%d%d", &x, &y, &c);
		G.addEdge(x, y, c);
	}
	printf("%d", G.Maxflow()); 
	return 0;
}
