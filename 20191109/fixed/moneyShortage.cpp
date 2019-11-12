#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <vector>

using namespace std;

#define FILE_IO
#ifdef FILE_IO
	#define FILE moneyShortage
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif


int n, m, q;

struct query{
	int val, id, ans;
	query(int val = 0, int id = 0, int ans = 0):val(val),id(id),ans(ans){}
	bool operator< (const query& rhs) const{return val < rhs.val;}
}querys[100020];

struct Graph{
	struct Edge
	{
		int from, to, weight;
		Edge(int from = 0, int to = 0, int weight = 0):from(from),to(to),weight(weight){};
		bool operator< (const Edge& rhs) const{return weight < rhs.weight;}
	}edges[100020];

	struct union_find{
		int fa[100020]; int size[100020]; int aim;
		union_find():aim(0){for(int i = 0; i < 100003; i++) fa[i] = i, size[i] = 1;}
		int find(int x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
		bool _union(int i, int j, int k){
			int x = find(i), y = find(j);
			if(x == y) return 0;
			fa[x] = y;
			while(aim < q && k > querys[aim].val) aim++;
			if(aim < q) querys[aim].ans += size[x] * size[y]; 
			size[y] += size[x];
			return 1;
		}
	} uf;

	void kruskal(int m, int q){
		sort(edges, edges + m); sort(querys, querys + q);
		for(int i = 0; i < m; i++){
			uf._union(edges[i].from, edges[i].to, edges[i].weight);
		}
		for(int i = 1; i < q; i++){
			if(querys[i].val != querys[i - 1].val){
				querys[i].ans += querys[i - 1].ans;
			}
			else{
				querys[i].ans = querys[i - 1].ans; 
			}
		}
	}
}G;

int out[100020];

int main(){
#ifdef FILE_IO
	start;
#endif
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 0, u, v, w; i < m; i++){
		scanf("%d%d%d", &u, &v, &w);
		G.edges[i] = Graph::Edge(u, v, w);
	}
	for(int i = 0, L; i < q; i++){
		scanf("%d", &L); querys[i] = query(L, i);
	}
	G.kruskal(m, q);
	for(int i = 0; i < q; i++){
		out[querys[i].id] = querys[i].ans;
	}
	for(int i = 0; i < q; i++){
		printf("%d ", out[i]);
	}
	return 0;
}
