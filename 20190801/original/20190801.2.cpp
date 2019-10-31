#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <ctime>
#include <cstring>
using namespace std;
int a[50005];
int dp[2][1000005];
int mod[1000005];
int main(){
	int T, k, n, tmp;
	scanf("%d", &T);
	while(T--){
		memset(dp, 0, sizeof(dp));
		memset(mod, 0, sizeof(mod));
		scanf("%d%d", &k, &n);
		for(int i = 0; i < n; i++){
			scanf("%d", &tmp);
			a[i] = tmp%k;
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < k; j++){
				dp[i&1][j] = dp[!(i&1)][(j+k-a[i])%k];
				mod[j] += dp[i&1][j];
			}
			dp[i&1][a[i]]++;
			mod[a[i]]++;
		}
		printf("%d\n", mod[0]);
	}	
	return 0;
}
