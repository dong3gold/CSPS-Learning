#include <cstdio>
#include <cstring>
using namespace std;
int prime[500], tot = 0;
long long f[1020];
void prime_table(int n){
	bool vis[1020];
	memset(vis, 0, sizeof(vis));
	for(int i = 2; i <= n; i++){
		if(vis[i]) continue;
		prime[++tot] = i;
		for(int j = i; j <= n; j+=i){
			vis[j] = 1;
		}
	}
}
int main(){
	int n;
	memset(f, 0, sizeof(f));
	f[0] = 1;
	memset(prime, 0 ,sizeof(prime));
	scanf("%d", &n);
	prime_table(n);
	for(int i = 1; i <= tot; i++){
		for(int j = n; j >= prime[i]; j--){
			for(int k = prime[i]; k <= j; k*=prime[i])
				f[j] += f[j-k];
		}
	}
	long long ans = 0;
	for(int i = 0; i <= n; i++){
		ans += f[i];
	}
	printf("%lld\n", ans);
	return 0;
}
