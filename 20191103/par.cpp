#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>

using namespace std;
bool vis[2000010];
int pow_10[10];
int c[10];
int T, L, R, len;
long long ans;

int main(){
	pow_10[0] = 1; c[0] = 0; for(int i = 1; i < 8; i++) pow_10[i] = pow_10[i-1] * 10, c[i] = c[i-1] + i;
	scanf("%d", &T);
	while(T--){
		memset(vis, 0, sizeof(vis));
		scanf("%d%d", &L, &R); if(R < 19 && printf("0\n")) continue;
		len = 0;
		while(pow_10[++len] <= L);
		for(int i = L; i <= R; i++){ if(vis[i]) continue;
			int t = 0; vis[i] = 1;
			for(int k = 1, g; k < len; k++){
				g = i / pow_10[k] + i % pow_10[k] * pow_10[len - k];
				if(g >= L && g <= R &&!vis[g]) vis[g] = 1, t++; 
			}
			ans += c[t];
		}
		printf("%lld\n", ans); ans = 0;
	}
	return 0;
}
