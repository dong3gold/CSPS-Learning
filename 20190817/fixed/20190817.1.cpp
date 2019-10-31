#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
bool vis[1005];
int prime[505];
int num[1005][500];
long long int m[105][1005];
int seive(int n){
	vis[1] = 1; int tot = 0; memset(num, 0, sizeof(num)); memset(vis, 0, sizeof(vis));
	for(int i = 2; i <= n; i++){
		if(!vis[i]){
			prime[tot] = i;
			for(int j = i; j <= n; j+=i){
					vis[j] = 1;
					int p = j, nm = 0;
					while(p && p%i == 0) p/=i, nm++;
					for(int k = j; k <= n; k++){
						num[k][tot] += nm;
					}
			}
			tot++;
		}
	}
	return tot;
}
int times, n;

int main(){
	scanf("%d%d", &n, &times);
	memset(m, 0, sizeof(m));
	if(times >= 1 && n > 1){
		int t = seive(n);
		if(times == 1){
			long long sum = 1;
			for(int i = 0; i < t; i++){
				sum *= num[n][i] + 1;
				sum %= 1000000009;
			}
			printf("%lld\n", sum);
			return 0;
		}
		else if(times == 2){
			long long sum = 1;
			for(int i = 1; i <= n; i++){
				for(int j = 0; j < t; j++){
					m[1][j] += (long long) num[i][j] %  1000000009;
					m[1][j] %= 1000000009;				
				}
			}
			for(int i = 0; i < t; i++){
				sum *= m[1][i] + 1;
				sum %= 1000000009;
			}
			printf("%lld\n", sum);
			return 0;
		}
		for(int i = 1; i <= n; i++){
			m[1][i] = 1;
			m[2][i] = n - i + 1;
		}
		int k = 2;
		while(++k < times){
			for(int i = 1; i <= n; i++){
				for(int j = i; j <= n; j++){
					m[k][i] += m[k-1][j];
					m[k][i] %= 1000000009;
				}
			}
		}
		long long sum = 1;
		for(int j = 1; j <= n; j++){
			for(int i = 0; i < t; i++){
				m[k][i] += (long long) m[times-1][j] * num[j][i] %  1000000009;
				m[k][i] %= 1000000009;
			}
		}
		for(int i = 0; i < t; i++){
			sum *= m[k][i] + 1;
			sum %= 1000000009;
		}
		printf("%lld\n", sum);
		return 0;
	}
	else if(n <= 1){
		printf("1\n");
		return 0;
	}
	else if(times == 0){
		printf("%d\n", n);
		return 0;
	}
}
