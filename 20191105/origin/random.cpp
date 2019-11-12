#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <vector>

using namespace std;
long long dp[5010][5010];
int pre[5010], fa[5010];
vector<int> depth[5010];
int vis[5010];
int n, k, maxd = 0;

int head[5010], next[10200], v[10200], cnt;

void addEdge(int from, int to){
	cnt++; v[cnt] = to; next[cnt] = head[from]; head[from] = cnt;
}

void dfs(int u, int p, int d){
	if(vis[u]) return;
	maxd = max(d, maxd);
	vis[u] = 1; depth[d].push_back(u); fa[u] = p;
	for(int i = head[u]; i; i = next[i]){
		dfs(v[i], u, d+1);
	}
}


int main(){
	freopen("random.in", "r", stdin); freopen("random.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for(int i = 1, u, v; i <= n; i++){
		scanf("%d%d", &u, &v); addEdge(u, v); addEdge(v, u);
	}
	dp[1][0] = 1;
	for(int i = 1; i <= n; i++){
		dp[1][i] = k;
	}
	for(int i = 2; i <= n; i++){
		for(int j = 1; j <= n; j++){
			for(int l = j - 1; l >= 0; l--){
				dp[i][j] = dp[fa[i]][l] * k % 998244353;
			}
		}
	}
	long long ans = 1;
	for(int i = 1; i <= n; i++){
		ans = (dp[maxd][i] + ans) % 998244353;
	}
	printf("%lld", ans);
	return 0;
}

