#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cctype>
#include <queue>

using namespace std;

bool trans[250][25];
int ans = 0;

struct AC{
	int trie[250][26];
	int fail[250];
	int val[250];
	int trie_cnt, s_cnt;
	static const int root = 0;
	AC():trie_cnt(0),s_cnt(1){memset(trie, 0, sizeof(trie)); memset(val, 0, sizeof(val));memset(fail, 0, sizeof(fail));}
	
    #define id(a) ((a) - 'a')
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
		fail[0] = 0;
		for(int i = 0; i < 26; i++){
			if(trie[0][i]) q.push(trie[0][i]);
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
	void query(char* s){
		int now = root;
		for(int i = 0; s[i]; i++){
			now = trie[now][id(s[i])];
			for(int j = now; j; j = fail[j]) 
				if(val[j]) ans++;
		}
	}
	void clean(){
		trie_cnt = 0; s_cnt = 1;
		memset(trie, 0, sizeof(trie)); memset(val, 0, sizeof(val)); memset(fail, 0, sizeof(fail));
	}
};
AC aho; char T[220];

int dfs(char* ss){
    
}

int main(){

    return 0;
}