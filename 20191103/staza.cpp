#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

int a[120][120];
long long dp[120][120];
long long staza[120][120];
long long mn = 0x7f7f7f7f7f7f7f, ans = 0;
int n;

int main(){
	while(~scanf("%d", &n) && n){
		memset(staza, 0, sizeof(staza)); memset(dp, 0, sizeof(dp)); mn = 0x7f7f7f7f7f7f7f, ans = 0;
		for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) scanf("%d", &a[i][j]);
		for(int i = 0; i < n; i++) for(int j = n - i - 2; j >= 0; j--) a[i][j] += a[n - j - 1][n - i - 1];
		dp[0][0] = a[0][0]; staza[0][0] = 1;
		for(int i = 1; i < n; i++) dp[0][i] = dp[0][i-1] + a[0][i], staza[0][i] = 1;
		for(int i = 1; i < n; i++) dp[i][0] = dp[i-1][0] + a[i][0], staza[i][0] = 1;
		for(int i = 1; i < n; i++){
			for(int j = 1; j < n; j++){
				//printf("dp[%d][%d] : %d, dp[%d][%d] %d\n", i-1, j, dp[i-1][j],  i, j-1, dp[i][j-1]);
				if(dp[i-1][j] < dp[i][j-1]) dp[i][j] = dp[i-1][j] + a[i][j], staza[i][j] = staza[i-1][j];
				else if(dp[i][j-1] < dp[i-1][j]) dp[i][j] = dp[i][j-1] + a[i][j], staza[i][j] = staza[i][j-1];
				else dp[i][j] = dp[i][j-1] + a[i][j], staza[i][j] = staza[i-1][j] + staza[i][j-1];
			}
		}
		for(int i = 0; i < n; i++) if(mn > dp[n - i - 1][i]) mn = dp[n - i - 1][i];
		//printf("mn : %d\n", mn);
		for(int i = 0; i < n; i++) if(mn == dp[n - i - 1][i]) ans += staza[n - i - 1][i];
		printf("%lld\n", ans);
	}
	return 0;
}
