#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
template <typename T>
struct Edge{
	int next, to;
	T dist;
	Edge():next(0),to(0){};
	Edge(int next, int to, T dist):next(next),to(to),dist(dist){};
};
template <typename T>
struct HeapNode{
	int to; T dist;
	bool operator < (const HeapNode& x) const{
		return x.dist < this->dist;
	}
};

template <typename T, int N>
struct Graph{
	int head[N];
	Edge<T> edge[N];
	int cnt, n;
	T d[N]; bool vis[N];
	priority_queue<HeapNode<T> > q;
	Graph():cnt(0){}
	void addEdge(int form, int to, T dist){
		cnt++;
		edge[cnt] = Edge<T>(head[form], to, dist);
		head[form] = cnt;
	}
	void Dijkstra(int s){
		memset(vis, 0, sizeof(vis)); memset(d, 0x3f, sizeof(d));
		d[s] = 0;
		q.push((HeapNode<T>){s, 0});
		while(!q.empty()){
			HeapNode<T> x = q.top(); q.pop();
			int u = x.to;
			if(vis[u]) continue;
			vis[u] = 1;
			for(int i = head[u]; i; i = edge[i].next){
				Edge<T>& e = edge[i];
				if(d[e.to] > d[u] + e.dist) {
					d[e.to] = d[u] + e.dist;
					q.push((HeapNode<T>){e.to, d[e.to]});
				}
			}
		}
	}
	void Printd(){
		for(int i = 1; i <= n; i++){
			printf("%d ", d[i]);
		}
		printf("\n");
	}
};

Graph<int, 300000> G;


int main(){
	int n, m, s;
	scanf("%d%d%d", &n, &m, &s);
	G.n = n;
	int u, e, v;
	for(int i = 0; i < m; i++){
		scanf("%d%d%d", &u, &e, &v);
		G.addEdge(u, e, v);
	}
	G.Dijkstra(s);
	G.Printd();
}

