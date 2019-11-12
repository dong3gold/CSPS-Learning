#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <queue>

using namespace std;

int n, m, k;
char s[250];
char temp[250];
int ans = 0x7f7f7f7f;

struct AC{
	int trie[250][26];
	int fail[250];
	int val[250];
	int fa[250][25];
	int trie_cnt, s_cnt;
	static const int root = 0;
	AC():trie_cnt(0){memset(trie, 0, sizeof(trie)); memset(val, 0, sizeof(val));memset(fail, 0, sizeof(fail)); memset(fa, 0, sizeof(fa));}
	
	#define id(a) ((a) - 'a')
	void insert(char *s){
		int now = root; int i = 0;
		while(*s){
			if(!trie[now][id(*s)]) trie[now][id(*s)] = ++trie_cnt;
			now = trie[now][id(*s)];
			s++; i++;
		}
		val[now] = i;
	}
	void dfs(int u, int pre, int d){
		fa[u][1] = pre;
		for(int i = 0; i < 26; i++){
			if(trie[u][i]) dfs(trie[u][i], u, d+1);
		}
		for(int i = 1; i <= d; i++) fa[u][i] = fa[pre][i-1];
	}
	void build(){
		queue<int> q;
		fail[0] = 0;
		for(int i = 0; i < 26; i++){
			if(trie[0][i]) {
				q.push(trie[0][i]);
				dfs(trie[0][i], 0, 1);
			}
		}
		while(!q.empty()){
			int x = q.front(); q.pop();
			for(int i = 0; i < 26; i++){
				if(trie[x][i]){
					fail[trie[x][i]] = trie[fail[x]][i];
					q.push(trie[x][i]);
				}
				else{
					trie[x][i] = trie[fail[x]][i];
				}
			}
		}
	}

	void query(int i, int pre, int k, int len){
		if(!k || !s[i]){
			ans = min(ans, len);
			return ;
		} 
		int now = pre;
		for(int j = i; s[j]; j++){
			now = trie[now][id(s[j])];
			for(int t = now; t; t = fail[t]){
				query(j + 1, fa[now][val[t]], k-1, len - val[t]);
			}
		}
	}
	void clean(){
		trie_cnt = 0; s_cnt = 1;
		memset(trie, 0, sizeof(trie)); memset(val, 0, sizeof(val)); memset(fail, 0, sizeof(fail));
	}
};
AC aho;

int main(){
	scanf("%d%d%d", &n, &m, &k);
	scanf("%s", s);
	for(int i = 0; i < m; i++){
		scanf("%s", temp);
		aho.insert(temp);
	}
	aho.build();
	aho.query(0, 0, k, n);
	printf("%d", ans);
	return 0;
}