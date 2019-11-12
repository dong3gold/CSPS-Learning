#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <set>

using namespace std;
int n, m;
struct light
{
	int l, r, a;
	light(){}
	light(int l, int r, int a):l(l),r(r),a(a){}
	bool operator < (const light& b) const {
		return l == b.l ? r == b.r ? a > b.a : r < b.r : l < b.l;
	}
}lights[300010];

long long dp[300010];
int la[300010];
set<int> in[300010];
set<int> used;

int main(){
	//freopen("cover.in", "r", stdin); freopen("cover.out", "w", stdout);
	scanf("%d%d", &n ,&m);
	for(int i = 0, l, r, a; i < m; i++){scanf("%d%d%d", &l, &r, &a); lights[i] = light(l, r, a);}
	sort(lights, lights + m);
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++) la[j] = 0;
		for(int j = 0; j < m; j++){
			int trans = 0; bool chosen = 0;
			int now = lights[j].r;
			for(int k = 0; k < lights[j].r; k++){
				if(la[k] < lights[j].l && in[k].find(j) == in[k].end()) 
					if(dp[k] + lights[j].a > dp[now]) 
						dp[now] = dp[k] + lights[j].a, trans = k, chosen = 1;
				else if(dp[now] < dp[k]) 
					dp[now] = dp[k], trans = k, chosen = 0;
			}
			in[now] = in[trans]; la[now] = la[trans];
			if(chosen) in[now].insert(j), la[now] = lights[j].l;
		}
		printf("%lld ", dp[lights[m-1].r]);
		dp[0] = dp[lights[m-1].r];
		used = in[lights[m-1].r];
		if(used.size() == m) {
			for(int j = i + 1; j < m; j++) printf("%lld ", dp[m-1]);
		}
	}
	return 0;
}
