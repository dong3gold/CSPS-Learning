#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <map>

#define FILE_IO
#ifdef FILE_IO
	#define FILE bag
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif

using namespace std;
int n, m, T;
struct thing{
	int weight, value;
	thing(int weight = 0, int value = 0):weight(weight),value(value){}
	bool operator< (const thing& b) const{return weight == b.weight ? value < b.value : weight < b.weight;}
}things[1002];
int bags[1002];

int dp[1002][1002];

int main(){
#ifdef FILE_IO
	start;
#endif
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 0, w, v; i < n; i++){
			scanf("%d%d", &w, &v);
			things[i] = thing(w, v);
		}
		scanf("%d", &m);
		for(int i = 0, w; i < m; i++){
			scanf("%d", &w);
			bags[i] = w;
		}
		sort(things, things + n);
		sort(bags, bags + m);
		memset(dp, 0, sizeof(dp));
		for(int i = 0; things[i].weight <= bags[0] && i < n; i++){
			dp[0][i] = 1;
		}
		for(int i = 1; i < m; i++){
			for(int j = 0; j < n; j++){
				if(dp[i-1][j]){
					for(int k = j + 1; things[k].weight <= bags[i] && k < n; k++){
						if(things[k].value >= things[j].value){
							dp[i][k] = max(dp[i][k], dp[i-1][j] + 1);
						}
					}
				}
				else {
					for(int k = 0; things[k].weight <= bags[i] && k < n; k++){
						dp[i][k] = max(dp[i][k], 1);
					}
				}
				dp[i][j] = max(dp[i][j], dp[i-1][j]);
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i++){
			ans = max(dp[m-1][i], ans);
		}
		printf("%d\n", ans);
	}
	return 0;
}
