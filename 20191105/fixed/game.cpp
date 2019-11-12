#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <typeinfo>
using namespace std;

long long dp[200010][3][2][3];
char s[200010]; bool same = 0, all_same = 1;

int main(){
	freopen("game.in", "r", stdin); freopen("game.out", "w", stdout);
	for(int i = 0; i < 3; i++) dp[1][i][0][i] = 1;
	for(int i = 2; i <= 200000; i++){
		for(int j = 0; j < 3; j++){
			for(int k = 0; k < 3; k++){
				dp[i][j][0][k] = dp[i][j][1][k] = 0;
				for(int l = 0; l < 3; l++){
					if(k != l) dp[i][j][0][k] = (dp[i][j][0][k] + dp[i-1][(3+j-k)%3][0][l]) % 998244353;
					else dp[i][j][1][k] = (dp[i][j][1][k] + dp[i-1][(3+j-k)%3][0][l]) % 998244353;
					dp[i][j][1][k] = (dp[i][j][1][k] + dp[i-1][(3+j-k)%3][1][l]) % 998244353;
				}
			}
		}
	}
	scanf("%s", s);
	int i = 0; int sum = 0;
	for(; s[i]; i++){
		if(s[i]==s[i+1]) same = 1;
		else if(s[i+1] != 0) all_same = 0; 
		sum += s[i] - 97; 
	}
	if(i == 3){
		if(s[0] == s[1] && s[1] == s[2] && printf("1\n")) return 0;
		if((s[0] == s[1] || s[1] == s[2]) && printf("6\n")) return 0;
		if(s[0] == s[2] && printf("7\n")) return 0;
		printf("3\n"); return 0;
	}
	sum %= 3;
	long long ans = 0;
	for(int j = 0; j < 3; j++) ans += dp[i][sum][1][j];
	if(!same) ans++;
	ans %= 998244353;
	if(!all_same) printf("%lld\n", ans);
	else printf("%lld\n", 1ll);
	return 0;
}

int main(){
	return 0;
}
