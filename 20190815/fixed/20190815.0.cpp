#include <cstdio>
#include <algorithm>

using namespace std;
int a[1005], b[1005];
int main() {
	int n; long long sum = 0;
	n = 1000;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	for(int i = 0; i < n; i++){
		scanf("%d", &b[i]);
	}
	sort(a, a + n);
	sort(b, b + n);
	for(int i = 0; i < n; i++){
		sum += (long long) a[i] * b[n - 1 - i];
	}
	printf("%lld", sum);
	return 0; 
} 
