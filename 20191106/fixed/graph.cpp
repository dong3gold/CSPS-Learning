#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <vector>
#include <stack>

#define FILE_IO
#ifdef FILE_IO
	#define FILE graph
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif

using namespace std;

int n, m;

struct Graph
{
	struct Edge
	{
		int from, to, next, id;
		Edge(int from = 0, int to = 0, int next = 0, int id = 0):from(from),to(to),next(next),id(id){}
	}edges[2000020];
	int cnt, head[1000010];
	void addEdge(int from, int to, int id){
		edges[++cnt] = Edge(from, to, head[from], id); head[from] = cnt;
	}

	Graph():cnt(0){memset(head, 0, sizeof(head));}

	int pre[1000010], iscut[1000010], bccno[1000010], bccnode[1000010], dfs_clock, bcc_cnt;
	bool tag[1000010];
	vector<int> bcc[1000010];
	
	stack<int> S;
	
	int dfs(int u, int fa){
		int lowu = pre[u] = ++dfs_clock;
		int child = 0;
		for(int i = head[u]; i; i = edges[i].next){
			int v = edges[i].to;
			if(!pre[v]){
				S.push(i);
				child++;
				int lowv = dfs(v, u);
				lowv = min(lowu, lowv);
				if(lowv >= pre[u]){
					iscut[u] = 1;
					bcc_cnt++; bcc[bcc_cnt].clear();
					for(;;){
						int x = S.top(); S.pop();
						if(bccno[edges[x].from] != bcc_cnt) {bcc[bcc_cnt].push_back(x); bccno[edges[x].from] = bcc_cnt; bccnode[bcc_cnt]++;}
						if(bccno[edges[x].to] != bcc_cnt) {if(bcc[bcc_cnt].back() != x) bcc[bcc_cnt].push_back(x); bccno[edges[x].to] = bcc_cnt; bccnode[bcc_cnt]++;}
						if(edges[x].from == u || edges[x].to == v) break;
					}
					if(bcc[bcc_cnt].back() != i)bcc[bcc_cnt].push_back(i);
				}
			}
			else if(pre[v] < pre[u] && v != fa){
				S.push(i);
				lowu = min(lowu, pre[v]);
			}
		}
		if(fa < 0 && child == 1) iscut[u] = 0;
		return lowu;
	}

	void find_bcc(int n){
		memset(pre, 0, sizeof(pre));
		memset(iscut, 0, sizeof(iscut));
		memset(bccno, 0, sizeof(bccno));
		memset(bccnode, 0, sizeof(bccnode));
		dfs_clock = bcc_cnt = 0;
		for(int i = 1; i <= n; i++){
			if(!pre[i]) dfs(i, -1);
		}
	}

	void solve(int n){
		memset(tag, 0, sizeof(tag));
		int ans = 0;
		find_bcc(n);
		for(int i = 0; i <= n; i++){
			if((int)bcc[i].size() == bccnode[i]) {
				for(int j = 0; j < bccnode[i]; j++) 
					tag[edges[bcc[i][j]].id] = 1;
			}
		}
		for(int i = 1; i <= m; i++) if(tag[i]) ans ^= i;
		printf("%d\n", ans);
	}
}G;

int main(){
	start;
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v; i <= m; i++){
		scanf("%d%d", &u, &v);
		G.addEdge(u, v, i);
		G.addEdge(v, u, i);
	}
	G.solve(n);
	return 0;
}
