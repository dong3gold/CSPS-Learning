#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <tuple>
#include <unordered_map>

using namespace std;

int a[10000];
int c[10000];

void f(int k, int l, int r){
	if(l == r) a[l]++;
	else if(k == 1){
		for(int i = l; i <= r; i++) a[i]++;
	}
	else for(int i = l; i <= r; i++){
		for(int j = i; j <= r; j++){
			f(k - 1, i, j);
		}
	}
}

int k, r; long long ans = 0;
int main(){
	scanf("%d%d", &k, &r);
	for(int i = 1; i <= r; i++) scanf("%d", c + i);
	if(k == 1){
		for(int i = 1; i <= r; i++){
			ans += c[i];
			printf("%lld ", ans);
		}
	}
	for(int i = 1; i <= r; i++){
		memset(a, 0, sizeof(a)); ans = 0;
		f(k, 1, i);
		for(int j = 1; j <= i; j++){
			ans += c[i] * a[i];
		}
		printf("%lld ", ans);
	}
	return 0;
}