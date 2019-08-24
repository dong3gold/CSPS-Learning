#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <queue>
#include <vector>
#include <cmath>
#include <limits>
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
		memset(vis, 0, sizeof(vis));
		for(int i = 0; i < cnt; i++){
			d[i] = numeric_limits<T>::max();
		}
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
	void clean(){
		memset(head, 0, sizeof(head));
		memset(edge, 0, sizeof(edge));
		memset(d, 0, sizeof(d));
		cnt = n = 0;
		while(!q.empty()) q.pop();
	}
};

struct Node{
	int x, y, z, r;
	Node():x(0),y(0),z(0),r(0){}
	Node(int x, int y, int z, int r):x(x),y(y),z(z),r(r){}
}nodes[120]; int tot = 1;
long double dist(int i, int j){
	return max(0.0L, sqrt(static_cast<long double>(static_cast<long long>(nodes[i].x - nodes[j].x) * (nodes[i].x - nodes[j].x) + static_cast<long long>(nodes[i].y - nodes[j].y) * (nodes[i].y - nodes[j].y) + static_cast<long long>(nodes[i].z - nodes[j].z) * (nodes[i].z - nodes[j].z))) - nodes[i].r - nodes[j].r);
}

Graph<long double, 300000> G;
int n, x, y, z, r;
int main(){
    freopen("warp.in", "r", stdin); freopen("warp.out", "w", stdout);
    while(scanf("%d", &n) == 1){
    	tot = 1;
    	if(n == -1) return 0;
    	for(int i = 0; i < n; i++){
    		scanf("%d%d%d%d", &x, &y, &z, &r);
    		nodes[tot++] = Node(x, y, z, r);
		}
		scanf("%d%d%d", &x, &y, &z);
    	nodes[0] = Node(x, y, z, 0);
    	scanf("%d%d%d", &x, &y, &z);
    	nodes[n+1] = Node(x, y, z, 0);
    	for(int i = 0; i <= n + 1; i++){
    		for(int j = 0; j <= n + 1; j++){
    			if(i != j){
    				G.addEdge(i, j, dist(i, j));
				}
			}
		}
		G.Dijkstra(0);
		printf("%lld\n", static_cast<long long>(ceil(G.d[n+1] * 10 - 0.5)));
		G.clean();
	}
	return 0;
}
