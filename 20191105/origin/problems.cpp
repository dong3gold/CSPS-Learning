#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;

int n, m, e;
template <int N, int M>
struct Graph{
	struct Edge{
		int u, v, pre, next;

		Edge():u(0),v(0),next(0){}
		Edge(int u, int v, int next):u(u),v(v),next(next){}
	} edges[M];
	int head[N], cnt;
	bool vis[N]; int match[N], matchE[N];
	int problems[N], del[M], delcnt;

	Graph():cnt(0){memset(head, 0, sizeof(head)); memset(vis, 0, sizeof(vis)); memset(match, 0, sizeof(match));}

	void addEdge(int from, int to){
		edges[++cnt] = Edge(from, to, head[from]); head[from] = cnt;
	}

	void build(){
		for(int i = 1; i <= n; i++){
			edges[head[i]].pre = 0;
			for(int j = head[i]; j && edges[j].next; j = edges[j].next){
				edges[edges[j].next].pre = j;
			}
		}
	}
	
	bool find(int u){
		if(vis[u]) return 0;
		vis[u] = 1;
		for(int i = head[u]; i; i = edges[i].next){
			int v = edges[i].v;
			if(!match[v] || find(match[v])){
				match[v] = u; matchE[v] = i;
				return 1;
			}
		}
		return 0;
	}

	void KM(){
		memset(match, 0, sizeof(match)); memset(matchE, 0, sizeof(matchE)); memset(problems, 0, sizeof(problems)); memset(del, 0, sizeof(del));
		delcnt = 0;
		for(int i = 1; i <= n; i++) {memset(vis, 0, sizeof(vis)); find(i);}
		for(int i = 1; i <= n; i++){
			if(match[i] && !problems[i] && !problems[match[i]]){
				problems[i] = match[i]; del[delcnt++] = matchE[i];
				printf("%d %d ", match[i], i);
			}
		}
		printf("\n");
		for(int i = 0; i < delcnt; i++){
			if(del[i] == head[edges[del[i]].u]) head[edges[del[i]].u] = edges[del[i]].next, edges[edges[del[i]].next].pre = 0;
			else if(edges[del[i]].next == 0) edges[edges[del[i]].pre].next = 0;
			else edges[edges[del[i]].next].pre = edges[del[i]].pre, edges[edges[del[i]].pre].next = edges[del[i]].next;
		}
	}
};

Graph<5010, 25000020> G;

int main(){
	freopen("problems.in", "r", stdin); freopen("problems.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			G.addEdge(i, j);
		}
	}
	G.build();
	for(int i = 1; i < n; i++){
		G.KM();
	}
	return 0;
}