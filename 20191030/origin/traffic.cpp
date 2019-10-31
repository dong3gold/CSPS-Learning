#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;
int n, a;
struct Graph{
	int mp[6020][6020];
	Graph(){}
	
	void addEdge(int u, int v){
		mp[u][v] = 1;
	}
	
	void clear(){
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) mp[i][j] = 0x3f3f3f3f;
	}
	
	void floyd(){
		for(int k = 1; k <= n; k++){
			for(int i = 1; i <= n; i++){
				for(int j = 1; j <= n; j++){
					mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
				}
			}
		}
	}
}G;


int main(){
	freopen("traffic.in", "r", stdin); freopen("traffic.out", "w", stdout);
	scanf("%d", &n); G.clear();

	for(int i = 2; i <= n; i++){
		scanf("%d", &a);
		for(int j = a; j <= i; j++){
			G.addEdge(i, j);
		}
	}
	for(int i = 2; i <= n; i++){
		scanf("%d", &a);
		for(int j = a; j <= i; j++){
			G.addEdge(j, i);
		}
	}
	for(int i = 1; i <= n; i++){
		G.mp[i][i] = 0;
	}
	G.floyd();
	int ans = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			ans ^= (i+j) * G.mp[i][j];
		}
	}
	printf("%d\n", ans);
	return 0;
}

