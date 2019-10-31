#include <cstdio>
#include <algorithm>

using namespace std;
int F[1020], E[1020], W[1020];
int n; int head[1020], to[1020], next[1020], edges[1020];
int cnt = 0;
void addEdge(int form, int to){
	++cnt;
	next[cnt] = head[form];
	to[cnt] = to;
	head[form] = cnt;
}
void dfs(int u){
	if(u){
		for(int i = head[u]; i; i = next[i]){
			dfs(i);
		}
	}
	if(E[u] < W[u]){
		for(int i = head[u]; i; i = next[i]){
			F[i] = F[u];
		}
	}
}


int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d%d", F + i, E + i, W + i);
		addEdge(F[i], i);
	}
	
	return 0;
}
