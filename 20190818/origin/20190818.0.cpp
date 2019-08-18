#include <cstdio>
#include <algorithm>
#include <cctype> 
#include <queue>
using namespace std;
int n; int a[10200], b[10200], c[10200]; long long sum[10200];
queue<int> q;
bool cmp(int x, int y){ return b[x] == b[y] ? a[x] < a[y] : b[x] < b[y]; }
int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){scanf("%d%d", a + i, b + i); c[i] = i; sum[i] = i ? sum[i-1] + a[i] : a[i]; }
	long long ans = 0, s = 0; int ai = 0;
	for(int i = 0; i < n; i++){while(!q.empty()) if(b[c[i]] > b[q.front()]) q.pop(); q.push(c[i]); s = 0; for(int j = 0; j < q.size(); j++) s += b[c[j]]; int j = 1; for(;i + j < n && a[c[i + j]] < b[c[i]]; j++) s += b[c[i]]; if(ans < s + (sum[n-1] - sum [i+j-1])) ans = s + (sum[n-1]-sum[i+j-1]), ai = i;}
	printf("%lld %d", ans, b[c[ai]]);
	return 0;
}
