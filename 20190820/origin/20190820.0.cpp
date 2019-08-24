#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
int n, m, s, big;
int read(){
	char ch = 0; int X = 0;
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) {X = (X << 3) + (X << 1) + (ch ^ 48); ch = getchar();}
	return X;
}
struct Edge{
	int next, to, dist;
	Edge():next(0),to(0),dist(0){}
	Edge(int next, int to, int dist):next(next),to(to),dist(dist){}
}edges[7000002];

int headE[7000002], cnt;
void addEdge(int from, int to, int dist){
	cnt++;
	edges[cnt] = Edge(headE[from], to, dist);
	headE[from] = cnt;
}

struct Node{
	int x, y, next;
	Node():x(0),y(0),next(-1){}
	Node(int x, int y, int next):x(x),y(y),next(next){}
}nodes[2000020];
int headN[2000020];
void addNode(int x, int y, int dist, int lvl){
	if(dist == lvl && dist == 0) return ;
	big = max(big, lvl);
	nodes[y*m+x] = Node(x, y, headN[lvl]);
	nodes[y*m+x+s] = Node(x, y, -1);
	addEdge(y*m + x, y*m + x + s, dist);
	headN[lvl] = y*m + x;
}
int mp[1002][1002];
int dis(Node i, Node j){
	return abs(i.x - j.x) + abs(i.y - j.y);
}

long long d[2000020]; long long int mx = 0;
bool inq[2000020];
void SPFA(){
	queue<int> q; memset(inq, 0, sizeof(inq));
	int t = 0;
	while(!(~headN[t])) t++;
	for(int i = headN[t]; ~i; i = nodes[i].next){
		q.push(i); d[i] = 0; inq[i] = 1;
	}
	while(!q.empty()){
		int x = q.front(); q.pop();
		inq[x] = 0;
		for(int i = headE[x]; i; i = edges[i].next){
			Edge& e = edges[i];
			if(d[e.to] < d[x] + e.dist){
				d[e.to] = d[x] + e.dist;
				mx = max(mx, d[e.to]);
				if(!inq[e.to]){
					q.push(e.to);
					inq[e.to] = 1;
				}
			}
		}
	}
}

int main(){
	n = read(), m = read();
	s = n * m; big = 0;
	memset(headN, -1, sizeof(headN));
	memset(headE, 0, sizeof(headE));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			mp[i][j] = read();
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			addNode(j, i, read(), mp[i][j]);
		}
	}
	for(int i = 0; i < big; i++){
		for(int j = headN[i]; ~j; j = nodes[j].next){
			int p = i + 1;
			while(!(~headN[p])) p++;
			for(int k = headN[p]; ~k; k = nodes[k].next){
				addEdge(j+s, k, dis(nodes[j], nodes[k]));
			}
		}
	}
	SPFA();
	printf("%lld\n", mx);
	return 0;
}
