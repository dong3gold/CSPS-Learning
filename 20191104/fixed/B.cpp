#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define is_B_capital 1
using namespace std;
const int maxM = 100010, maxN = 3010;

int n, m, K, lim;
int mp[maxN][maxN], s[maxN], cnt[maxM];
bool down[maxN][maxN], upp[maxN][maxN];
long long ans_sum = 0; int ans_max = 0;
unsigned int f[maxM][maxN / 32 + 5];

int read(){
	char ch(0); int x(0);
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) {x = (x << 3) + (x << 1) + (ch^48); ch = getchar();}
	return x;
}

#define clz(x) __builtin_clz(x)
#define ctz(x) __builtin_ctz(x)

void add(unsigned int *f, int x){
	int y = x >> 5, pre = -1, suf = -1;
	if(f[y]){
		int o = x & 31; unsigned int z = f[y];
		for(int i = o-1; i >= 0; i--){
			if(z >> i & 1){
				pre = y << 5 | i; break;
			}
		}
		for(int i = o+1; i < 32; i++){
			if(z >> i & 1){
				suf = y << 5 | i; break;
			}
		}
	}
	if(pre < 0){
		for(int i = y - 1; i >= 0; i--){
			if(f[i]) {pre = i << 5 | (31 - clz(f[i])); break;}
		}
	}
	if(suf < 0){
		for(int i = y + 1; i < lim; i++){
			if(f[i]) {suf = i << 5 | ctz(f[i]); break;}
		}
	}
	int l = max(pre + 1, x - K + 1), r = min(suf - K, x);
	if(l <= r) {s[l]++, s[r+1]--;}
	f[y] ^= 1U << (x & 31);
}

void del(unsigned int *f, int x){
	int y = x >> 5, pre = -1, suf = -1;
	f[y] ^= 1U << (x & 31);
	if(f[y]){
		int o = x & 31; unsigned int z = f[y];
		for(int i = o-1; i >= 0; i--){
			if(z >> i & 1){
				pre = y << 5 | i; break;
			}
		}
		for(int i = o+1; i < 32; i++){
			if(z >> i & 1){
				suf = y << 5 | i; break;
			}
		}
	}
	if(pre < 0){
		for(int i = y - 1; i >= 0; i--){
			if(f[i]) {pre = i << 5 | (31 - clz(f[i])); break;}
		}
	}
	if(suf < 0){
		for(int i = y + 1; i < lim; i++){
			if(f[i]) {suf = i << 5 | ctz(f[i]); break;}
		}
	}
	int l = max(pre + 1, x - K + 1), r = min(suf - K, x);
	if(l <= r) {s[l]--, s[r+1]++;}
}

int main(){
	n = read(); m = read(); K = read();
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			mp[i][j] = read();
		}
	}
	for(int i = 1; i < maxM; i++){
		f[i][0] = 1;
		f[i][(m+1)>>5] |= 1U << ((m+1) & 31); 
	}
	lim = (m+1) >> 5;
	for(int i = 1, d, u; i <= m; i++){
		for(d = 1; d < K; d++){
			if(!(cnt[mp[d][i]]++)){
				down[d][i] = 1;
			}
		}
		for(u = 0; d <= n; u++, d++){
			if(u) if(!(--cnt[mp[u][i]])) upp[u][i] = 1;
			if(!(cnt[mp[d][i]]++)) down[d][i] = 1;
		}
		for(int j = 1; j <= n; j++){
			cnt[mp[j][i]] = 0;
		}
	}
	//for(int i = 1; i <= n; i++, printf("\n")) for(int j = 1; j <= m; j++) printf("%d ", down[i][j]);
	for(int i = 1; i < K; i++){
		for(int j = 1; j <= m; j++){
			if(down[i][j])
				add(f[mp[i][j]], j);
		}
	}
	for(int i = K, k = 0; i <= n; i++, k++){
		if(k) for(int j = 1; j <= m; j++) if(upp[k][j])
			del(f[mp[k][j]], j);
		for(int j = 1; j <= m; j++) if(down[i][j]) 
			add(f[mp[i][j]], j);
		for(int j = 1, pre = 0; j <= m - K + 1; j++) {
			pre += s[j]; ans_max = max(ans_max, pre); ans_sum += pre;
		}
	}
	printf("%d %lld", ans_max, ans_sum);
	return isupper('B')^1;
}
