#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node{
	int E, v;
}a[1010];
int fa[1010], w[1010], n, ans;
bool operator < (node a, node b) {
	return a.E < b.E;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &fa[i], &a[i].E, &w[i]);
		a[i].v = i;
	}
	sort(a, a + n);
	for (int i = 1; i <= n; i++) {
		int j;
		for (j = a[i].v; j; j = fa[j]) if (w[j] < a[i].E) break;
		if (j) continue;
		for (j = a[i].v; j; j = fa[j])
			w[j] -= a[i].E;
		ans++;	
	}
	printf("%d\n", ans);
	return 0;
}

