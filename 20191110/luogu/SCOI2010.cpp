#include <cstdio>
#include <algorithm>
#include <cstring>

int n, m, e;
template <int M>
struct Graph{
    struct Edge{
        int v, w, next;
        /*
        Edge():v(0),w(0),next(0){}
        Edge(int v, int w, int next):v(v),w(w),next(next){}
        */
    } edges[M];
    int head[M], cnt;
    bool vis[M]; int match[M];

    Graph():cnt(0){memset(head, 0, sizeof(head)); memset(vis, 0, sizeof(vis)); memset(match, 0, sizeof(match));}

    void addEdge(int from, int to, int dist = 0){
        edges[++cnt] = {to, dist, head[from]}; head[from] = cnt;
    }
    
    bool find(int u){
        if(vis[u]) return 0;
        vis[u] = 1;
        for(int i = head[u]; i; i = edges[i].next){
            int v = edges[i].v;
            if(!match[v] || find(match[v])){
                match[v] = u;
                return 1;
            }
        }
        return 0;
    }

    int KM(){
        int ans = 0;
        for(int i = 1; i <= n; i++) {memset(vis, 0, sizeof(vis)); if(find(i)) ans++; else break;}
        return ans;
    }
};

Graph<2000010> G;

int main(){
	scanf("%d", &n);
	for(int i = 1, a, b; i <= n; i++){
		scanf("%d %d", &a, &b);
		G.addEdge(a, i); G.addEdge(b, i);
	}
	printf("%d\n", G.KM());
	return 0;
}