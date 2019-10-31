#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <queue>

using namespace std;

int n, limit;
int H[100020], G[100020], dp[100020];
long long sum[100020];
int l = 0, r = 0;
int ans, mid; 

deque<int> q;

bool check(int x){
	int p = 1;
	for(int i = 1; i <= n; i++){
		while(sum[i] - sum[p-1] > x) p++;
		while(!q.empty() && q.front() < p) q.pop_front();
		while(!q.empty() && H[q.back()] <= H[i]) q.pop_back();
		q.push_back(i);
		dp[i] = dp[p-1] + H[q.front()];
		for(int j = 0; j < q.size() - 1; j++) dp[i] = min(dp[i], dp[q[j]] + H[q[j+1]]);
		if(dp[i] > limit) return 0;
	}
	return 1;
}

int main(){
	scanf("%d%d", &n, &limit); sum[0] = 0, dp[0] = 0;
	for(int i = 1; i <= n; i++){
		scanf("%d%d", H + i, G + i);
		sum[i] = sum[i-1] + G[i];
		l = max(l, G[i]); r += G[i];
	}
	while(l <= r){
		mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}

