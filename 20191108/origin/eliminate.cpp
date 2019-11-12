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

int fail[1000010];
int failB[1000010];
char s[1000010];

void getfail(char *s, int n, int *fail){
	fail[0] = fail[1] = 0;
	for(int i = 1; i < n; i++){
		int j = fail[i];
		while(j && s[j] != s[i]) j = fail[j];
		fail[i+1] = s[i] == s[j] ? j + 1 : 0;
	}
}

int T;
int t = 0;

int main(){
	scanf("%d", &T);
	while(T--){
		t = 0;
		memset(fail, 0, sizeof(fail));
		memset(s, 0, sizeof(s));
		scanf("%s", s);
		int n = strlen(s);
		if(n == 1) {
			printf("0\n");
			continue;
		}
		getfail(s, n, fail);
		t = fail[n];
		while(t >= n / 2) t = fail[t];
		getfail(s + t, n - 2 * t, fail);
		t += fail[n - 2 * t];
		printf("%d\n", t);
	}
	return 0;
}
