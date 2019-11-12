#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define FILE_IO
#ifdef FILE_IO
	#define FILE match
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x)  to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif


long long f_2[65][2];
long long g_2[65][2];

long long f[10000000][2];
long long g[10000000][2];

void fun(long long x, long long &f0, long long &f1, long long &g0, long long &g1){
	if(x < 10000000) {f0 = f[x][0], f1 = f[x][1]; g0 = g[x][0], g1 = g[x][1]; return ;}
	if(x ^ (x & -x)){
		if(x & 1){
			long long _f0, _f1, _f2, _f3, _g0, _g1, _g2, _g3;
			fun((x >> 1) + 1, _f0, _f1, _g0, _g1); fun(x >> 1, _f2, _f3, _g2, _g3);
			f0 = _f1 + _f3;
			g0 = _g1 * _g3 % 998244353;
			if(_f1 + _f2 > _f0 + _f3){
				f1 = _f1 + _f2 + 1;
				g1 = _g1 * _g2 % 998244353;
			}
			else if(_f1 + _f2 < _f0 + _f3){
				f1 = _f0 + _f3 + 1;
				g1 = _g0 * _g3 % 998244353;
			}
			else {
				f1 = _f1 + _f2 + 1;
				g1 = (_g1 * _g2 % 998244353 + _g0 * _g3 % 998244353) % 998244353;
			}
			return ;
		}
		else{
			long long _f0, _f1, _g0, _g1;
			fun((x >> 1), _f0, _f1, _g0, _g1);
			f0 = _f1 << 1;
			f1 = _f0 + _f1 + 1;
			g0 = _g1 * _g1 % 998244353;
			g1 = (_g1 * _g0 << 1) % 998244353;
			return ;
		}
	}
	else{
		int k = 0;
		for(; 
			x ^ (1LL << k); 
			k++);
		f0 = f_2[k][0], f1 = f_2[k][1];
		g0 = g_2[k][0], g1 = g_2[k][1];
		return ;
	}
}

int T;
long long x, f0, f1, g0, g1;

int main(){
#ifdef FILE_IO
	start;
#endif
	f_2[0][0] = f_2[0][1] = 0; g_2[0][0] = 1; g_2[0][1] = 1; f_2[1][0] = 0; f_2[1][1] = 1; g_2[1][0] = 1; g_2[1][1] = 2;
	for(int i = 1; i < 65; i++){
		f_2[i+1][0] = f_2[i][1] << 1;
		f_2[i+1][1] = f_2[i][1] + f_2[i][0] + 1;
		g_2[i+1][0] = g_2[i][1] * g_2[i][1] % 998244353;
		g_2[i+1][1] = (g_2[i][1] * g_2[i][0] << 1) % 998244353;
	}
	f[1][0] = f[1][1] = 0; g[1][0] = g[1][1] = 1; f[2][0] = 0; f[2][1] = 1; g[2][0] = 1; g[2][1] = 2;
	for(int i = 3; i <= 9999999; i++ ){
		if(i & 1){
			f[i][0] = f[(i >> 1) + 1][1] + f[i >> 1][1];
			g[i][0] = g[(i >> 1) + 1][1] * g[i >> 1][1] % 998244353;
			if(f[(i >> 1) + 1][1] + f[i >> 1][0] > f[(i >> 1) + 1][0] + f[i >> 1][1]){
				f[i][1] = f[(i>>1)+1][1] + f[i>>1][0] + 1;
				g[i][1] = g[(i>>1)+1][1] * g[i>>1][0] % 998244353;
			}
			else if(f[(i>>1) + 1][1] + f[i >> 1][0] < f[(i>>1)+1][0] + f[i>>1][1]){
				f[i][1] = f[(i>>1)+1][0] + f[i>>1][1] + 1;
				g[i][1] = g[(i>>1)+1][0] * g[i>>1][1] % 998244353;
			}
			else{
				f[i][1] = f[(i>>1)+1][1] + f[i>>1][0] + 1;
				g[i][1] = (g[(i>>1)+1][0] * g[i>>1][1] % 998244353 + g[(i>>1)+1][1] * g[i>>1][0] % 998244353) % 998244353;
			}
		}
		else {
			f[i][0] = f[i >> 1][1] << 1;
			f[i][1] = f[i >> 1][1] + f[i >> 1][0] + 1;
			g[i][0] = g[i >> 1][1] * g[i >> 1][1] % 998244353;
			g[i][1] = (g[i >> 1][1] * g[i >> 1][0] << 1) % 998244353; 
		}
	}
	scanf("%d", &T);
	while(T--){
		scanf("%lld", &x);
		fun(x, f0, f1, g0, g1);
		if(f0 > f1){
			printf("%d %d\n", f0, g0);
		}
		else if(f0 < f1){
			printf("%d %d\n", f1, g1);
		}
		else printf("%d %d\n", f0, (g0 + g1) % 998244353);
	}
	return 0;
}