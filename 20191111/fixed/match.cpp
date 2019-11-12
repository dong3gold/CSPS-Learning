#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

//#define FILE_IO
#ifdef FILE_IO
	#define FILE match
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x)  to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif


map<long long, pair<pair<long long, long long>, pair<long long, long long> > > m;

void fun(long long x, long long &f0, long long &f1, long long &g0, long long &g1){
	if(m.find(x) != m.end()) {f0 = m[x].first.first, f1 = m[x].first.second; g0 = m[x].second.first, g1 = m[x].second.second; return ;}
	long long _f0, _f1, _f2, _f3, _g0, _g1, _g2, _g3;
	f0 = f1 = g0 = g1 = 0;
	fun((x + 1) >> 1, _f0, _f1, _g0, _g1); fun(x >> 1, _f2, _f3, _g2, _g3);
	f0 = max(max(_f0 + _f2, _f1 + _f3), max(_f0 + _f3, _f1 + _f2));
	if(f0 == _f0 + _f2) (g0 += _g0 * _g2 % 998244353) %= 998244353;
	if(f0 == _f1 + _f3) (g0 += _g1 * _g3 % 998244353) %= 998244353;
	if(f0 == _f0 + _f3) (g0 += _g0 * _g3 % 998244353) %= 998244353;
	if(f0 == _f1 + _f2) (g0 += _g1 * _g2 % 998244353) %= 998244353;
	f1 = max(max(_f0 + _f3 + 1, _f1 + _f2 + 1), _f0 + _f2 + 1);
	if(f1 == _f0 + _f3 + 1) (g1 += _g0 * _g3 % 998244353) %= 998244353;
	if(f1 == _f1 + _f2 + 1) (g1 += _g1 * _g2 % 998244353) %= 998244353;
	if(f1 == _f0 + _f2 + 1) (g1 += _g0 * _g2 * 2 % 998244353) %= 998244353;
	m[x] = make_pair(make_pair(f0, f1), make_pair(g0, g1));
	return ;
}

int T;
long long x, f0, f1, g0, g1;

int main(){
#ifdef FILE_IO
	start;
#endif
	scanf("%d", &T);
	while(T--){
		m.clear();
		m[1] = make_pair(make_pair(0, 0), make_pair(1, 0));
		scanf("%lld", &x);
		fun(x, f0, f1, g0, g1);
		if(f0 > f1){
			printf("%lld %lld\n", f0, g0);
		}
		else if(f0 < f1){
			printf("%lld %lld\n", f1, g1);
		}
		else printf("%lld %lld\n", f0, (g0 + g1) % 998244353);
	}
	return 0;
}