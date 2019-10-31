#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <queue>
#include <set>
using namespace std;
int n, m, k; int u, v;
int d[55][55]; set<int> G[55], G2[55];
void addEdge(int u, int v){
	G[u].insert(v);
	G2[v].insert(u);
	d[u][v] = 1;
}

int main(){
    freopen("bus.in", "r", stdin); freopen("bus.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    memset(d, 0x3f, sizeof(d));
    for(int i = 1; i <= m; i++){
    	scanf("%d%d", &u, &v);
    	addEdge(u, v); 
	}
	for(int i = 1; i <= n; i++) d[i][i] = 0;
	for(int k = 1; k <= n; k++){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
	if(d[1][n] > k) {
		printf("0\n");
		return 0;
	}
	int ans = 0, ans2 = 0;
	for(set<int>::iterator i = G[1].begin(); i != G[1].end(); i++){
		if(d[*i][n] < k) ans++;
	}
	for(set<int>::iterator i = G2[n].begin(); i != G2[n].end(); i++){
		if(d[1][*i] < k) ans2++;
	}
	printf("%d\n", min(ans, ans2));
	return 0;
}
