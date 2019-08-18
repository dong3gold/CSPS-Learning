#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;
int n;
double p[25][25];
double dp[25][25][25];
int main(){
	scanf("%d", &n); int A;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			scanf("%d", &A);
			p[i][j] = (double) A / 100;
		}
	}
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= n; j++){
			for(int k = 0; k <= n; k++){
				dp[i][j][k] = 0.0;
			}
		}
	}
	dp[0][0][0] = 1;
	dp[1][0][0] = p[1][1];
	dp[1][1][1] = 1;
	for(int i = 2; i <= n; i++){
		dp[i][0][0] = max(dp[i-1][0][0] * p[i][i], dp[i][0][0]);
		for(int j = 1; j < i; j++){
			for(int k = 1; k < i; k++){
				dp[i][0][0] = max(dp[i][0][0], dp[i-1][j][k] * p[i][k] * p[j][i]);
				dp[i][i][k] = max(dp[i][i][k], dp[i-1][j][k] * p[j][i]);
				dp[i][j][i] = max(dp[i-1][j][k] * p[i][k], dp[i][j][k]);
				dp[i][j][k] = max(dp[i-1][j][k] * p[i][i], dp[i][j][k]);
			}
		}
	}
	printf("%.6f", dp[n][0][0] * 100);
	return 0;
}
