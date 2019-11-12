#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cmath>

using namespace std;
long long sum = 0;
long long trans_sum = 0;
long long max_trans = 0;
int n, k; long long a[1000010], pre = 0;

int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i < n; i++){
		scanf("%lld", &a[i]);
		pre = i >= k ? a[i - k] : a[1];
		sum += a[i];
		trans_sum += a[i] - (i >= k ? pre : 0);
		max_trans = max(trans_sum, max_trans);
	}
	printf("%lld\n", sum - (k ? max_trans : 0));
	return 0;
}