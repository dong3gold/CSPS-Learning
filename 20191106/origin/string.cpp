#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <queue>

#define FILE_IO
#ifdef FILE_IO
	#define FILE string
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif

using namespace std;

int n, m;
int a[210];
char s[210];

struct AC
{
	#define root 0
	#define id(x) ((x)-97)
	int tr[210][26], fail[210];
	int val[210]; int cnt;
	long long _dp[210][210];
	AC():cnt(0){memset(val, 0, sizeof(val)); memset(tr[root], 0, sizeof(tr[root])); memset(fail, 0, sizeof(fail));}

	void insert(char *s, int a){
		int now = root;
		while(*s){
			if(!tr[now][id(*s)]) tr[now][id(*s)] = ++cnt;
			now = tr[now][id(*s)];
			s++;
		}
		val[now] = a;
	}
	
	queue<int> q;
	void build(){
		for(int i = 0; i < 26; i++){
			if(tr[root][i]) {q.push(tr[root][i]); fail[tr[root][i]] = root;}
		}
		while(!q.empty()){
			int x = q.front(); q.pop();
			for(int i = 0; i < 26; i++){
				if(tr[x][i]) {
					fail[tr[x][i]] = tr[fail[x]][i]; q.push(tr[x][i]);
				}
				else tr[x][i] = tr[fail[x]][i];
			}
		}
	}

	long long query(int now){
		long long ans = 0;
		for(;now; now = fail[now]){
			ans += val[now];
		}
		return ans;
	}

	long long dp(){
		memset(_dp, -1, sizeof(_dp));
		_dp[0][0] = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j <= cnt; j++){
				for(int k = 0; k < 26; k++){
					if(~_dp[i][j]) {
						long long delta = query(tr[j][k]);
						_dp[i+1][tr[j][k]] = max(_dp[i][j] + delta, _dp[i+1][tr[j][k]]);
					}
				}
			}
		}
		long long ans = 0;
		for(int i = 0; i <= cnt; i++){
			ans = max(ans, _dp[n][i]);
		}
		return ans;
	}

	#undef id
	#undef root
}aho;

int main(){
#ifndef LOCAL
	#ifdef FILE_IO
		start;
	#endif
#endif
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++){
		scanf("%d", &i[a]);
	}
	for(int i = 0; i < m; i++){
		scanf("%s", s);
		aho.insert(s, i[a]);
	}
	aho.build();
	printf("%lld", aho.dp());
	return 0;
}
