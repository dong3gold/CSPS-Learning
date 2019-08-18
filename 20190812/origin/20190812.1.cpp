#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#define ms(x) memset(x, 0, sizeof(x))
using namespace std;
int p[100200];
int n, a[100200], left[100200], right[100200]; 
int last[100200], mx[100200], l, r, dp[100200];
int main(){
	freopen("array.in", "r", stdin);
	freopen("array.out", "w", stdout);
    scanf("%d", &n); ms(last);
    l = 0; r = n; 
    for(int i = 1; i <= n; i++){
        scanf("%d%d", p + i, a + i);
        l = max(last[p[i]], l);
        left[i] = l;
        last[p[i]] = i;
    }
  	ms(mx); memset(dp, 0x7f, sizeof(dp));
  	dp[0] = 0;
    for(int i = 1; i <= n; i++){
    	for(int j = left[i]; j < i; j++){
    		mx[j+1] = max(mx[j+1], a[i]);
            dp[i] = min(dp[i], dp[j] + mx[j+1]);
        }
	}
	printf("%d\n", dp[n]);
    return 0;
}
