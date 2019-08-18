#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define id(x) ((x) - 'a')
using namespace std;
int ans[153];
char str[153][72];
bool cmp(int x, int y){
	if(ans[x] == ans[y]) return x < y;
	return ans[x] > ans[y];
}
struct AC{
	int trie[11000][26];
	int last[11000];
	int val[11000];
	int trie_cnt, s_cnt;
	static const int root = 0;
	AC():trie_cnt(0),s_cnt(1){memset(trie, 0, sizeof(trie)); memset(val, 0, sizeof(val)); memset(ans, 0, sizeof(ans)); memset(last, 0, sizeof(last));}
	
	void insert(char *s){
		int now = root;
		while(*s){
			if(!trie[now][id(*s)]){
				trie[now][id(*s)] = ++trie_cnt;
			}
			now = trie[now][id(*s)];
			s++;
		}
		val[now] = s_cnt++;
	}
	void build(){
		queue<int> q;
		last[0] = 0;
		for(int i = 0; i < 26; i++){
			if(trie[0][i]) q.push(trie[0][i]);
		}
		while(!q.empty()){
			int x = q.front(); q.pop();
			for(int i = 0; i < 26; i++){
				if(trie[x][i]){
					last[trie[x][i]] = trie[last[x]][i];
					q.push(trie[x][i]);
				}
				else{
					trie[x][i] = trie[last[x]][i];
				}
			}
		}
	}
	void query(char* s){
		int now = root;
		while(*s){
			now = trie[now][id(*s)];
			for(int j = now; j; j = last[j]) 
				if(val[j]) ans[val[j]]++;
			s++;
		}
		int r[153];
		for(int i = 1; i < s_cnt; i++) r[i] = i;
		sort(r+1, r+s_cnt, cmp);
		printf("%d\n", ans[r[1]]);
		printf("%s\n", str[r[1]]);
		for(int i = 2; ans[r[i]] == ans[r[i-1]]; i++){
			printf("%s\n", str[r[i]]);
		}
	}
	void clean(){
		trie_cnt = 0; s_cnt = 1;
		memset(trie, 0, sizeof(trie)); memset(val, 0, sizeof(val)); memset(ans, 0, sizeof(ans));
		memset(str, 0, sizeof(str)); memset(last, 0, sizeof(last));
	}
};
AC aho; char T[1002000];
int main(){
	int n;
	while(scanf("%d", &n) == 1){
		if(!n) return 0;
		for(int i = 1; i <= n; i++){
			scanf("%s", str[i]);
			aho.insert(str[i]);
		}
		aho.build();
		memset(T, 0 , sizeof(T));
		scanf("%s", T);
		aho.query(T);
		aho.clean();
	}
}
