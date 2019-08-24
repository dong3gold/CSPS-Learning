#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <queue>
#define lowbit(x) (x&-x)
using namespace std;
int n, m;
int nodes[20], edges[20][20];
int fa[20];
struct Edge
{
    int v, u, d;
    bool operator < (const Edge& x){return d < x.d;}
}edge[410];

int count(int x){
    int k = 0;
    while(x){x -= lowbit(x); k++;}
    return k;
}

int find(int x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
int kruskal(int* ch){
    int ans = 0;
    memset(edge, 0, sizeof(edge)); int tot = 0;
    for(int i = 0; i < m; i++){
        fa[i] = i;
        for(int j = 0; j < m; j++){
            if(i != j) edge[tot++] = (Edge){i, j, edges[ch[i]][ch[j]]};
        }
    }
    sort(edge, edge + tot);
    for(int i = 0; i < tot; i++){
        Edge& e = edge[i]; int x = find(e.u), y = find(e.v);
        if(x != y) ans += e.d, fa[y] = x;
    }
    return ans;
}
int main(){
    freopen("ratio.in", "r", stdin); freopen("ratio.out", "w", stdout);
    scanf("%d%d", &n, &m);
    if(n == m){
        for(int i = 1; i <= n; i++) printf("%d ", i);
        return 0;
    }
    for(int i = 1; i <= n; i++) scanf("%d", nodes + i); 
    for(int i = 1; i <= n; i++){
        for(int j = 1 ; j <= n; j++){
            scanf("%d", edges[i] + j);
        }
    }
    int ch[17], Enode = 0, mch[17];
    long double mn = 0x7fffffff; int la = 1 << n;
    for(int i = 0; i < la; i++){
    	if(count(i) != m) continue;
        memset(ch, 0, sizeof(ch)); Enode = 0;
        for(int j = i, cnt = 0, num = 1; j; j >>= 1, num++){
            if(j&1){
            	ch[cnt++] = num; Enode += nodes[num];
			}
        }
        long double ans = static_cast<long double>(kruskal(ch)) / Enode;
        if(ans < mn){
            mn = ans;
            for(int j = 0; j < m; j++) mch[j] = ch[j];
        }
        else if(ans <= mn){
        	int j = 0;
        	while(mch[j] == ch[j]) j++;
        	if(j < m && mch[j] > ch[j]){
        		for(int k = 0; k < m; k++){
        			mch[k] = ch[k];
				}
			}
		}
    }
    sort(mch, mch + m);
    for(int i = 0; i < m; i++) printf("%d ", mch[i]);
    printf("\n");
    return 0;
}
