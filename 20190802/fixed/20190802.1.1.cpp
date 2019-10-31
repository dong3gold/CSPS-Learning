#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <cstring>
using namespace std;
int n;
bool a[101];
int dp[220][220];
int s[220][220];
int ans = 0;
int tot = 0;
bool readOdd(){
	bool X; char ch = 0;
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)){
		X = ch & 1;
		ch = getchar();
	}
	tot += X;
	return X;
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		a[i] = a[n+i] = readOdd();
	}
	for(int j = 1; j <= n*2; j++){
		for(int i = 1; i <= n*2; i++){
			s[i][j] = 0;
			for(int k = i; k <= j; k++){
				s[i][j] += a[k];
			}
		}
	}
	for(int k = 1; k <= n; k++){
		memset(dp, 0, sizeof(dp));
		for(int i = 1; i <= n*2; i++) dp[i][i] = a[i];
		for(int i = k + n - 1; i > k ; i--){
			for(int j = i + 1; j <= k + n - 1; j++){
				dp[i][j] = s[i][j] - min(dp[(i+1)][j], dp[i][(j-1)]);
			}
		}
		if(s[k][(k+n-1)] - dp[k+1][(k+n-1)] > dp[(k+1)][(k+n-1)]) ans++;
	}
	printf("%d\n", ans);
	return 0;
}
