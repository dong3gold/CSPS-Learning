#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <limits>
#include <queue>
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
int n, m, k, e; int v, u, w; int days, l, r, x;
int next[101];
template<int N>
struct Graph{
	struct Edge{
		int next, to, dist;
		Edge():next(0),to(0),dist(0){}
		Edge(int next, int to, int dist):next(next),to(to),dist(dist){}
	};
	struct HeapNode{
		int to, dist;
		bool operator < (const HeapNode& x){return dist < x.dist;}
	};
	int head[N], cnt; Edge edges[N*N*2];
	int d[N]; bool vis[N], unable[N]; int p[N], tot, avl[102], len[102];
	Graph():cnt(0),tot(0){memset(head, 0, sizeof(head)); memset(unable, 0, sizeof(unable)); for(int i = 0; i < 102; i++) avl[i] = 1;}
	void addEdge(int form, int to, int dist){
		cnt++;
		edge[cnt] = Edge(head[form], to, dist);
		head[form] = cnt;
	}
	void Dijkstra(int s, int t){
		priority_queue<HeapNode> q; memset(d, 0x3e, sizeof(d)); memset(vis, 0, sizeof(vis));
		d[s] = 0;
		q.push((HeapNode){s, 0});
		while(!q.empty()){
			HeapNode x = q.top(); q.pop();
			int u = x.to; if(vis[u] || unable[t][u]) continue;
			vis[u] = 1;
			for(int i = head[u]; i; i = edges[i].next){
				Edge &e = edges[i];
				if(d[e.to] < d[i] + e.dist && !unable[t][e.to]){
					d[e.to] = d[i] + e.dist;
					p[e.to] = u;
					q.push((HeapNode){e.to, d[e.to]});
				}
			}
		}
		for(int i = p[m]; i; i = p[i]){
			if(unable[next[t]][i]) avl[t] = 0; 
		}
		len[t] = d[m];
	}
};
Graph<25> G;
int day[202], tot = 0, c[202];
bool cmp(int x, int y){return day[x] < day[y];}
int dp[102];

int main(){
    scanf("%d%d%d%d", &n, &m, &k, &e);
    for(int i = 0; i < e; i++){
    	scanf("%d%d%d", &v, &u, &w);
    	G.addEdge(v, u, w);
    	G.addEdge(u, v, w);
	}
	scanf("%d", &days);
	for(int i = 0; i < days; i++){
		scanf("%d%d%d", &x, &l, &r);
		day[tot] = l; c[tot] = tot++; 
		day[tot] = r; c[tot] = tot++;
		for(int j = l; j <= r; j++) G.unable[j][x] = 1;  
	}
	sort(c, c+tot, cmp); next[days[c[tot-1]]] = n + 1;
	for(int i = tot - 2; i >= 0; i--){
		if(c[i+1]&1) next[days[c[i]]] = days[c[i+1]] + 1;
		else next[days[c[i]]] = days[c[i+1]];
	}
	G.Dijkstra(1, 0);
	for(int i = days[c[0]]; i != n + 1; i = next[i]){
		G.Dijkstra(1, i);
	}
	dp[days[c[0]]] = (days[c[0]] - 1) * len[0]; int pre = days[c[0]];
	for(int i = days[c[1]]; i != n + 1; i = next[i]){
		dp[i] = dp[pre] + len[pre] * (i - 1 - pre) + k;
		if(G.avl[pre]) dp[i] = min(dp[i], )
	}
    return 0;
}
