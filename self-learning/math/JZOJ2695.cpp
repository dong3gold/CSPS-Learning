#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

static const int N = 1e7 + 7;
int inv[N], prime[N]; long long fac[N], mul[N];
bool vis[N];
int tot = 0;
int T, R;


int main(){
	memset(vis, 0, sizeof(vis));
	scanf("%d%d", &T, &R);
	fac[1] = 1;
	for(int i = 2; i < N; i++){
		fac[i] = (long long) fac[i-1] * i % R;
	}
	inv[1] = 1;
	for(int i = 2; i < N && i < R; i++){
		inv[i] = (long long) (R - R / i) * inv[(R % i)] % R;
	}
	for(int i = 2; i < N; i++){
		if(!vis[i]) prime[tot++] = i;
		for(int j = 0; j < tot && i * prime[j] < N; j++){
			vis[i*prime[j]] = 1;
			if(!(i % prime[j])) break;
		}
	}
	mul[1] = 1;
	for(int i = 2; i < N; i++){
		mul[i] = mul[i - 1];
		if(!vis[i]) mul[i] = (long long) mul[i] * (i - 1) % R * inv[i%R] % R; 
	}
	int n, m;
	for(int i = 0; i < T; i++){
		scanf("%d%d", &n, &m);
		printf("%d\n", (long long) fac[n] * mul[m] % R);
	}
	return 0;
}
