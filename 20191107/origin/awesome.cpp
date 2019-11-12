#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <map>

#define FILE_IO
#ifdef FILE_IO
	#define FILE awesome
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif

using namespace std;
long long n, p;
long long a[2444], cnt = 0;

long long rev(int x){
	if(x == 1) return 1;
	return (p - p / x) * rev(p % x) % p;
}

struct num{
	long long x, r, v; int cnt;
	num():x(0),cnt(0){}
	num(int x, int cnt):x(x),r(x % p),v(rev(r)),cnt(cnt){}
}nums[2444];

map<long long, int> mp;
long long ans = 0;


int main(){
#ifdef FILE_IO
	start;
#endif
	scanf("%lld%lld", &n, &p);
	for(int i = 0; i < n; i++){
		scanf("%lld", i + a);
	}
	sort(a, a + n);
	for(int i = 0, j = 1; i < n; i = j, j = i + 1){
		while(a[i] == a[j]) j++;
		nums[cnt++] =  num(a[i], j - i);
		mp[nums[i].v]++;
	}
	for(int i = 0; i < cnt; i++){
		if(nums[i].cnt == 2){
			if(nums[i].r * nums[i].r % p == nums[i].v) ans += mp[nums[i].r * nums[i].r % p] - 1;
			else ans += mp[nums[i].r * nums[i].r % p];
		}
		else if(nums[i].cnt >= 3){
			ans += mp[nums[i].r * nums[i].r % p];
		}
		for(int j = i + 1; j < cnt; j++){
			if(nums[i].cnt != 1 || nums[i].v != nums[i].r * nums[j].r)
				ans += mp[nums[i].r * nums[j].r % p];
			else ans += mp[nums[i].r * nums[j].r % p] - 1;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
