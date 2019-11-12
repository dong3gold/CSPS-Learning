#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;
//SCC ,Tarjan
vector<int> G[10020];
int pre[10020], lowlink[10020], sccon[10020], dfs_clock, scc_cnt;
stack<int> S;
void dfs(int u){
	pre[u] = lowlink[u] = ++scc_cnt;
	S.push(u);
	for(unsigned int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		if(!pre[v]){
			dfs(v);
			lowlink[v] = min(lowlink[v], lowlink[u]);
		} else if(!sccon[v]){
			lowlink[u] = min(lowlink[u], pre[v]);
		}
	}
	if(lowlink[u] == pre[u]) {
		scc_cnt++;
		for(;;){
			int x = S.top();
			sccon[x] = scc_cnt;
			if(x == u) break;
		}
	}
}
void find_scc(int n){
	dfs_clock = scc_cnt = 0;
	memset(sccon, 0, sizeof(sccon));
	memset(pre, 0, sizeof(pre));
	for(int i = 0; i < n; i++){
		if(!pre[i]) dfs(i);
	}
}
int main(){
	
	return 0;
}
