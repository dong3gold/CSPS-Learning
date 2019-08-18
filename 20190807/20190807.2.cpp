#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
struct Edge{
	int next, to;
	Edge():next(0),to(0){};
	Edge(int next, int to):next(next),to(to){};
};
struct HeapNode{
	int to; int dist;
	bool operator < (const HeapNode& x) const{
		return this->dist < x.dist;
	}
};

template <int N>
struct Graph{
	int head[N];
	Edge edge[N];
	int cnt, n;
	int d[N]; bool vis[N];
	bool visE[N];
	priority_queue<HeapNode > q;
	Graph():cnt(0){}
	void addEdge(int form, int to){
		cnt++;
		edge[cnt] = Edge(head[form], to);
		head[form] = cnt;
	}
	void Dijkstra(int s){
		memset(vis, 0, sizeof(vis)); memset(d, 0, sizeof(d));
		d[s] = 0;
		q.push((HeapNode){s, 0});
		while(!q.empty()){
			HeapNode x = q.top(); q.pop();
			int u = x.to;
			if(vis[u]) continue;
			vis[u] = 1;
			for(int i = head[u]; i; i = edge[i].next){
				Edge& e = edge[i];
				if(d[e.to] < d[u] + 1) {
					d[e.to] = d[u] + 1;
					q.push((HeapNode){e.to, d[e.to]});
				}
			}
		}
	}
	void printd(){
		int mx = 0;
		for(int i = 0; i < n; i++){
			mx = max(d[i], mx);
		}
		printf("%d", mx - 1);
	}
};

Graph<50000> G;


int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	G.n = n;
	int u, e, v;
	for(int i = 0; i < m; i++){
		scanf("%d%d", &u, &e);
		G.addEdge(u, e);
		G.addEdge(e, u);
	}
	G.Dijkstra(1);
	G.printd();
}

