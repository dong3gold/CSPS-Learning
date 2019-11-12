#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <vector>

#define FILE_IO
#ifdef FILE_IO
	#define FILE graph
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif

using namespace std;
bool vis[4020], visN[2010];
int pre[2010], low[2010];
int head[2010], nxt[4020], to[4020], id[4020];
bool isBridge[4020];
int cnt = 0;
int ans = 0;
int n, m;
void addEdge(int u, int v, int i){
	cnt++; nxt[cnt] = head[u]; to[cnt] = v; head[u] = cnt; id[cnt] = i;
}

int dfn = 0;

int dfs1(int u, int fa){
	int lowu = pre[u] = ++dfn;
	for(int i = head[u]; i; i = nxt[i]){
		int v = to[i];
		if(!pre[v]){
			int lowv = dfs1(v, u);
			lowu = min(lowu, lowv);
			if(lowv>pre[u]){
				isBridge[id[i]] = 1;
			}
		}
		else{
			if(pre[v] < pre[u] && v != fa){
				lowu = min(lowu, pre[v]);
			}
		}
	}
	low[u] = lowu;
	return lowu;
}

void dfs2(int u){
	visN[u] = 1;
	for(int i = head[u]; i; i = nxt[i]){
		if(!vis[id[i]] && !isBridge[id[i]]){
			ans ^= id[i]; vis[id[i]] = 1;
			dfs2(to[i]);
		}
	}
}

void find(){
	for(int i = 1; i <= n; i++) if(!visN[i]) dfs2(i);
}


int main(){
#ifndef LOCAL
	#ifdef FILE_IO
		start;
	#endif
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v; i <= m; i++){
		scanf("%d%d", &u, &v); addEdge(u, v, i); addEdge(v, u, i);
	}
	dfs1(1, -1);
	find();
	printf("%d", ans);
	return 0;
}
