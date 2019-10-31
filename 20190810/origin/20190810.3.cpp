#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cctype>
#include <map>
using namespace std;
int head[100020], nxt[100020];
int t[100020], cnt = 0, w[100020];
int n, m;
bool e[10020];
map<pair<int, int>, int> mp;
int read(){
	int X = 0, w = 0; char ch = 0;
	while(!isdigit(ch)){w|=ch=='-';ch = getchar();} 
	while(isdigit(ch)){X = (X<<1)+(X<<3)+(ch^48);ch=getchar();}
	return w ? -X : X;
}

bool addEdge(int to, int from){
	if(mp.find(make_pair(to, from)) != mp.end()){
		e[to] = e[from] = (e[to] | e[from]);
		return e[from]^1;	
	} 
	if(mp.find(make_pair(from, to)) == mp.end()){
		cnt++;
		nxt[cnt] = head[from];
		t[cnt] = to;
		w[cnt] = 1;
		head[from] = cnt;
		mp[make_pair(from, to)] = cnt;
		e[to] |= e[from];
	}
	else{
		w[mp[make_pair(from, to)]]++;
	}
	return 1;
}
long long d[100020]; bool flag = 0;
bool vis[100020];
bool dfs(int u){
	if(vis[u] || flag){
		flag = 1;
		return 0;
	}
	vis[u] = 1;
	for(int i = head[u]; i; i = nxt[i]){
		if(!dfs(t[i]) || flag) {
			flag = 1;
			return 0;
		}
	}
	vis[u] = 0;
	return 1;
}
queue<int> q;
void bfs(int s){
	vis[s] = 1;
	d[s] = 1;
	q.push(s);
	while(!q.empty()){
		int x = q.front(); q.pop();
		for(int i = head[x]; i; i = nxt[i]){
			vis[x] = 1;
			d[t[i]] += (w[i]*d[x])%1000000000;
			d[t[i]] %= 1000000000;
			q.push(t[i]);
		}
		if(vis[x]){
			d[x] = 0; vis[x] = 0;
		}
	}
}

int main(){
	n = read(); m = read();
	memset(vis, 0, sizeof(vis));
	memset(d, 0, sizeof(d));
	memset(e, 0, sizeof(e));
	memset(head, 0, sizeof(head));
	e[1] = 1;
	for(int i = 0; i < m; i++){
		if(!addEdge(read(), read())) {
			printf("inf\n");
			return 0;
		}
	}
	if(dfs(1)){
		memset(vis, 0, sizeof(vis));
		bfs(1);
		printf("%lld\n", d[2]);
	}
	else{
		printf("inf\n");
	}
	return 0;
}
