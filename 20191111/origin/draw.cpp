#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define FILE_IO
#ifdef FILE_IO
	#define FILE draw
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x)  to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif

int n, m;
long long l[20];
bool Edge[20][20];
long long c;
bool C[60], cnt = 0;
long long a[20];

unsigned int count(long long x){
	unsigned int k = 0;
	while(x) {x -= x & -x; k++;}
	return k;
}

bool flag = 0;

long long dfs(int d){
	if(d == -1){
		for(int i = 0; i < n; i++){
			for(int j = i + 1; j < n; j++){
				if(Edge[i][j] && (a[i] == a[j])) return 0;
			}
		}
		return 1;
	}
	long long ans = 0;
	for(long long i = 0; i < (1LL << n); i++){
		if((count(i) & 1) == C[d]){
			flag = 0;
			for(int j = 0; j < n; j++) 
				if((1LL << j) & i) {
					a[j] |= 1LL << d;
					if(a[j] > l[j]){
						flag = 1;
						break;
					}
				}
			if(!flag) ans = (ans + dfs(d - 1)) % 998244353;
			for(int j = 0; j < n; j++) a[j] &= ((1LL << n) - 1) - (1 << d);
		} 
	}
	return ans;
}

int main(){
	start;
	scanf("%d%d%lld", &n, &m, &c);
	while(c) {C[cnt++] = c & 1; c >>= 1;}
	for(int i = 0; i < n; i++) scanf("%lld", l + i);
	for(int i = 0, x, y;i < m; i++){scanf("%d%d", &x, &y); Edge[x-1][y-1] = Edge[y-1][x-1] = 1;}
	printf("%lld\n", dfs(59));
	return 0;
}