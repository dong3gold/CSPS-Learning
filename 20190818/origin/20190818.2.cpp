#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
struct AC{
	int tr[200000][26];
	int val[200000], fail[200000];
	long long int ans;
	static const int root = 0;
	int tot;
	AC():tot(0),ans(0){memset(tr, 0, sizeof(tr));memset(val, 0, sizeof(val));memset(fail, 0, sizeof(fail));}
	void insert(char *s){
		int t = root, len = 0;
		while(*s){
			int id = (*s) - 'a';
			if(!tr[t][id]){
				tr[t][id] = ++tot;
			}
			t = tr[t][id];
			len++;
		}
		val[t] = len;
	} 
	void build(){
		queue<int> q;
		q.push(root);
		while(!q.empty()){
			int t = q.front(); q.pop();
			for(int i = 0; i < 26; i++){
				if(tr[t][i]){
					fail[tr[t][i]] = tr[fail[t]][i]; 
				}
				else tr[t][i] = tr[fail[t]][i]; 
			} 
		}
	}
	long long int query(int n, char *s){
		int t = root, len = 0;
		while(*s){
			int id = (*s) - 'a';
			t = tr[t][id]; len++;
			for(int i = t; i; i = fail[i]) if(val[i] && (len <= n || val[i] + n < len)) ans++;
		}
		return ans;
	}
};
char s[200], T[200300];
::AC aho;
int main(){
	scanf("%s", s);
	aho.insert(s);
	scanf("%s", T);
	int n = strlen(T);
	aho.build();
	strcpy(T, T+n);
	printf("%lld\n", aho.query(n, T));
	return 0;
} 
