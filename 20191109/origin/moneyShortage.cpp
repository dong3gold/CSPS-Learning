#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <vector>

using namespace std;

struct Graph{
	struct Edge
	{
		int from, to, weight, next;
		Edge(int from, int to, int weight, int next):to(to),weight(weight),next(next){};
	}edges[100020], treeEdge[10020];int tree_cnt, treeHead[10020]; 
	int head[10020], cnt, root;
	int fa[10020][16], max_weight[10020][16];
	bool vis[10020];
	bool flag[100020];

	void addEdge(int from, int to, int weight){
		edges[++cnt] = Edge(from, to, weight, head[from]); head[from] = cnt;
	}

	struct union_find{
		int fa[100020];
		union_find(){for(int i = 0; i < 100003; i++) fa[i] = i;}
		int find(int x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
		bool _union(int i, int j){
			int x = find(i), y = find(j);
			if(x == y) return 0;
			fa[x] = y;
			return 1;
		}
	} uf;

	void dfs(int u){
		vis[u] = 1;
		for(int i = head[u]; i; i = edges[i].next){
			if(!flag[i]){
				int v = edges[i].to;
				if(!vis[v]){
					fa[v][0] = u; 
					treeEdge[++tree_cnt] = edges[i]; treeHead[u] = cnt;
					treeEdge[++tree_cnt] = Edge(v, u, edges[i].weight, treeHead[v]); treeHead[v] = cnt;
					max_weight[v][0] = edges[i].weight;
					dfs(v);
				}
			}
		}
	}

	Edge edges2[100010];
	bool cmp(Edge& lhs, Edge &rhs){return lhs.weight < rhs.weight;}
	void kruskal(int n, int m){
		for(int i = 1; i <= m; i++){
			edges2[i] = edges[i];
		}
		sort(edges2, edges2 + m, cmp);
		for(int i = 1; i <= m; i++){
			if(uf._union(edges2[i].from, edges2[i].to)){
				flag[i] = 1;
			}
		}
		dfs(1);
		for(int k = 1; k <= 15; k++){
			for(int i = 1; i <= n; i++){
				if(fa[i][k-1] > 0) 
				{
					fa[i][k] = fa[fa[i][k-1]][k-1];
					max_weight[i][k] = max(max_weight[fa[i][k-1]][k-1], max_weight[i][k-1]);
				}
			}
		}
	}
	
	int query(int L){
		
	}
};

int main(){

	return 0;
}