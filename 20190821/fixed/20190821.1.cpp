#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <queue>
#include <vector>
using namespace std;
int a[120], b[120];
int c[120], n, m;
bool cmp(int x, int y){ return a[x] < a[y] || (a[x] == a[y] && b[x] > b[y]);}
int dp[120][200];
bool check(int x){
	memset(dp, 0, sizeof(dp));
	int big = x / a[0];
	for(int i = 0; i <= big; i++){
		dp[0][i] = (x - i * a[0]) / b[0];
	}
	for(int i = 1; i < n; i++){
		int up = x / a[i];
		big += x / a[i];
		for(int j = 0; j <= big; j++){
			for(int k = 0; k <= up && j + k <= m; k++){
				dp[i][j+k] = max(dp[i][j+k], dp[i-1][j] + (x - k * a[i]) / b[i]);
			}
		}
	}
	return dp[n-1][m] >= m;
}

int main(){
    freopen("company.in", "r", stdin); freopen("company.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++){
    	scanf("%d%d", a + i, b + i); c[i] = i;
	}
	//sort(c, c + n, cmp);
	int l = 1, r = 10000, mid = (l + r) >> 1;
	while(l < r){
		if(!check(mid)){
			l = mid + 1;
		}
		else r = mid;
		mid = (l + r) >> 1;
	}
	printf("%d\n", mid);
	return 0;
}
