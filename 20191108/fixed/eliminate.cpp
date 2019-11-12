#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>

//#define FILE_IO
#ifdef FILE_IO
	#define FILE eliminate
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif

using namespace std;

int fail[1000010], failB[1000010];
int f[1000010];
char s[1000010];
int n;

void getfail(char *s, int n, int *fail){
	fail[0] = fail[1] = 0;
	for(int i = 1; i < n; i++){
		int j = fail[i];
		while(j && s[j] != s[i]) j = fail[j];
		fail[i+1] = s[i] == s[j] ? j + 1 : 0;
	}
}

typedef unsigned long long ull;
template <ull Base, ull mod>
struct Hash
{
	char* ch; ull hash[1000010];
	ull mi[1000010];
	ull operator() (const int& x, const int& y){
		return (hash[y] - hash[x-1] * mi[y - x + 1] % mod + mod) % mod;
	}
	void Make_Hash(){
		ch = s;
		hash[0] = ch[0]; mi[0] = 1;
		for(int i = 1; ch[i]; i++){
			mi[i] = mi[i-1] * Base % mod;
			hash[i] = (ch[i] + hash[i-1] * Base % mod) % mod;
		}
	}
};

Hash<19260817ULL, 1000000009ULL> hashTable;

int T;
int t = 0;

int main(){
	scanf("%d", &T);
	while(T--){
		t = 0;
		memset(fail, 0, sizeof(fail));
		memset(failB, 0, sizeof(failB));
		memset(s, 0, sizeof(s));
		scanf("%s", s);
		n = strlen(s);
		hashTable.Make_Hash();
		if(n == 1) {
			printf("0\n");
			continue;
		}
		getfail(s, n, fail);
		t = fail[n];
		while(t > n / 2) t = fail[t];
		getfail(s + t, n - t * 2, failB + t);
		f[t] = failB[n - t];
		for(int i = t; i; i = fail[i]){
			int j = min(f[i] + (i << 1) - fail[i] - 1, n / 2);
			for(; j; j--){
				if(hashTable(fail[i], j) == hashTable(n - j - 1, n - fail[i] - 1)) break;
			}
			if(j < fail[i]) break; else if(j == n / 2) {printf("%d\n", j); return 0;}
			f[fail[i]] = j - fail[i] + 1;
		}
		for(int i = t; i && f[i]; i = fail[i]) t = max(t, f[i] + i);
		printf("%d\n", t);
	}
	return 0;
}
