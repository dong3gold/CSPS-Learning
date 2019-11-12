#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <map>
#include<bits/stdc++.h>
//#pragma GCC optimize(3)
#define FILE_IO
#ifdef FILE_IO
	#define FILE awesome
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin)//, freopen(mask_out(FILE), "w", stdout)
#endif

using namespace std;
int n, p;
int a[2444], cnt = 0;

inline void read(register int &x){
	register char ch(0); x = 0;
	while(ch < 48) ch = getchar();
	while(ch > 47) {x = x * 10 + (ch^48); ch = getchar();}
}

inline int rev(const int& x){
	if(x == 1) return 1;
	return 1ll*(p - p / x) * rev(p % x) % p;
}

struct num{
	int x, r, v; int cnt;
	num():x(0),cnt(0){}
	num(const int& x,const int& cnt):x(x),r(x % p),v(rev(r)),cnt(cnt){}
}nums[2444];

unordered_map<int, int> mp;
int ans = 0;

int main(){
#ifdef FILE_IO
	start;
#endif
	//clock_t t1=clock();
	read(n), read(p);	
	for(register int *i=a,j=n;j--;read(*i++));
	sort(a, a + n);
	for(register int i = 0, j = 1; i < n; i = j, j = i + 1){
		while(a[i] == a[j]) ++j;
		nums[cnt++] =  num(a[i], j - i);
		++mp[nums[cnt-1].v];
	}
	for(register int i = 0, d = 0; i < cnt; ++i, d = 0){
		for(register int j = i + 1; j < cnt; ++j){
			d += mp[(long long)nums[i].r * nums[j].r % p];
			if((long long)nums[i].r * nums[j].r % p == nums[j].v) {if(nums[j].cnt >= 2) ++d; else --d;}
			if((long long)nums[i].r * nums[j].r % p == nums[i].v) {if(nums[i].cnt >= 2) ++d; else --d;}
		}
		ans += d >> 1;
		--mp[nums[i].v];
		if(nums[i].cnt >= 3 && (long long)nums[i].r * nums[i].r % p == nums[i].v) ++ans;
	}
	std::cout<<ans;
	return 0;
}
