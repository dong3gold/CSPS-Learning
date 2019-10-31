#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;

int n;

template <int N, int M>
struct Graph
{
    int head[N], cnt, next[M], to[M], from[M], nefrom[M], hefrom[M], deg[N], deg2[N];
    long long dist[N][2];
    bool inq[N], del[N];
    void addEdge(int u, int v)
    {
        to[++cnt] = v, next[cnt] = head[u], head[u] = cnt;
        from[cnt] = u, nefrom[cnt] = hefrom[v], hefrom[v] = cnt;
        deg[u]++, deg2[v]++;
    }
    Graph() : cnt(0)
    {
        memset(head, 0, sizeof(head));
        memset(deg, 0, sizeof(deg));
        memset(inq, 0, sizeof(inq));
    }
    int pre[10020], lowlink[10020], sccon[10020], dfs_clock, scc_cnt;

    stack<int> S;
    void dfs(int u)
    {
        pre[u] = lowlink[u] = ++scc_cnt;
        S.push(u);
        for (int i = head[u]; i; i = next[i])
        {
            int v = to[i];
            if (!pre[v])
            {
                dfs(v);
                lowlink[v] = min(lowlink[v], lowlink[u]);
            }
            else if (!sccon[v])
            {
                lowlink[u] = min(lowlink[u], pre[v]);
            }
        }
        if (lowlink[u] == pre[u])
        {
            scc_cnt++;
            for (;;)
            {
                int x = S.top(); S.pop();
                sccon[x] = scc_cnt;
                if (x == u)
                    break;
            }
        }
    }
    void find_scc(int n)
    {
        dfs_clock = scc_cnt = 0;
        memset(sccon, 0, sizeof(sccon));
        memset(pre, 0, sizeof(pre));
        for (int i = 1; i <= n; i++)
        {
            if (!pre[i])
                dfs(i);
        }
    }

    void solve(){
    	find_scc(n);
        queue<int> q;
        for(int i = 1; i <= n; i++){
            dist[i][0] = 0; dist[i][1] = 0x7f7f7f7f7fl;
            del[i] = 0;
            int j = head[i];
            for(; j; j = next[j]){
                if(sccon[i] != sccon[j]) break;
            }
            if(j == 0 && deg[i]){
                dist[i][0] = 0x7f7f7f7f7fl;
                del[i] = 1;
            } 
            if(deg[i] == 0){
                dist[i][0] = 0;
                dist[i][1] = 0;
                q.push(i);
            }
            if(deg2[i] == 0){
                dist[i][0] = 0;
            }
        }
        while(!q.empty()){
            int x = q.front(); q.pop();
            for(int i = hefrom[x]; i; i = nefrom[i]){
                int v = from[i];
                if(!del[i]){
                    if(dist[v][0] < dist[x][1] + 1){
                        dist[v][0] = dist[x][1] + 1;
                        if(!inq[v]) q.push(v);
                    }
                    if(dist[v][1] > dist[x][0] + 1){
                        dist[v][1] = dist[x][0] +1;
                        if(!inq[v]) q.push(v);
                    }
                }
            }
        }
        for(int i = 1; i <= n; i++){
            if(dist[i][0] == 0x7f7f7f7f7fl) printf("-1\n");
            else printf("%lld\n", dist[i][0]);
        }
    }
};

Graph<500050, 500050> G;

int m;
int main()
{
	freopen("idioms.in", "r", stdin); freopen("idioms.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        G.addEdge(u, v);
    }
    G.solve();
    return 0;
}
