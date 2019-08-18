#include <cstdio>
#include <cstring>
using namespace std;
//const long long num[10] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
long long dp[15][10];
long long solve(int x);

int main(){
	memset(dp, 0, sizeof(dp));
	for(int i = 0; i < 10; i++){
		dp[0][i] = 1;
	}
	for(int i = 1; i < 15; i++){
		for(int j = 0; j < 10; j++){
			for(int k = 0; k < 10; k++){
				if(k < j - 1 || k > j + 1) dp[i][j] += dp[i-1][k];
			}
		}
	}
	int A, B; scanf("%d%d", &A, &B);
	printf("%lld", solve(B+1) - solve(A));
	return 0;
}

long long solve(int x){
	int p = -1; long long ans = 0; int a[15];
	memset(a, 0, sizeof(a));
	while(x){a[++p] = x % 10; x /= 10;}
	for(int i = 0; i < p; i++){
		for(int j = 1; j < 10; j++) ans += dp[i][j]; 
	}
	for(int i = 1; i < a[p]; i++){
		ans += dp[p][i];
	}
	for(int i = p - 1; i >= 0; i--){
		for(int j = 0; j < a[i]; j++){
			if(j < a[i+1] - 1 || j > a[i+1]+1) ans += dp[i][j];
		}
		if(a[i] <= a[i+1] + 1 && a[i] >= a[i+1] - 1) break;
	}
	return ans;
}
