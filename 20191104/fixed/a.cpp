#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define in(x) freopen(x, "r", stdin)
#define out(x) freopen(x, "w", stdout)
using namespace std;

int m[5010][3], cnt = 0;
int r[5010];
long long dp[5010];

inline int dis(int a){return m[a][0] + m[a][1] + m[a][2];}
bool cmp(int x, int y) {return dis(x) < dis(y);}
int n, k;
long long rev[300010], mul[300010];
long long path[5010];

long long pow(long long a, int p){
	long long ans = 0;
	while(p){
		if(p&1) ans = ans * a % 1000000007;
		a = a * a % 1000000007;
	}
	return ans;
}

long long cacl(long long a){
	if(a == 1) return 1;
	return ((1000000007 - 1000000007 / a) * cacl(1000000007 % a)) % 1000000007;
}

void initRev(){
	long long end = 1; mul[0] = 1;
	for(int i = 1; i <= 300000; i++) end = end * i % 1000000007, mul[i] = end;
	end = cacl(end);
	//printf("%lld\n", end);
	for(int i = 300000; i > 0; end = end * i % 1000000007, i--) rev[i] = end; rev[0] = 1;
}

//返回p - (i -> j 的路径数) 
long long path_count(int x, int y, int z){
	return mul[x+y+z] * (rev[x] * (rev[y] * rev[z] % 1000000007) % 1000000007) % 1000000007;
}

int main(){
	//in("a.in"), out("a.out");
	initRev();
	scanf("%d%d", &n, &k);
	for(int i = 0, x, y, z; i < k; i++) 
		if(~scanf("%d%d%d", &x, &y, &z) && x <= n && y <= n && z <= n) 
		{
			if(x == n && y == n && z == n) {printf("0\n"); return 0;}
			m[cnt][0] = x, m[cnt][1] = y, m[cnt][2] = z; r[cnt] = cnt; cnt++;
		}
	m[cnt][0] = n, m[cnt][1] = n, m[cnt][2] = n; r[cnt] = cnt; cnt++;
	sort(r, r + cnt, cmp);
	for(int i = 0; i < cnt; i++){
		dp[i] = path_count(m[r[i]][0], m[r[i]][1], m[r[i]][2]);
		for(int j = 0; j < i; j++) if(m[r[j]][0] <= m[r[i]][0] && m[r[j]][1] <= m[r[i]][1] && m[r[j]][2] <= m[r[i]][2]){
			dp[i] -= dp[j] * path_count(m[r[i]][0] - m[r[j]][0], m[r[i]][1] - m[r[j]][1], m[r[i]][2] - m[r[j]][2]) % 1000000007;
			dp[i] = (dp[i] + 1000000007) % 1000000007;
		}
		if(m[r[i]][0] == n && m[r[i]][1] == n && m[r[i]][2] == n && printf("%lld\n", dp[i]))
			return 0;
	}
	return 0;
}
