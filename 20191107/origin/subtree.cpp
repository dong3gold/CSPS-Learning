#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <map>

#define FILE_IO
#ifdef FILE_IO
	#define FILE subtree
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif

using namespace std;
int n, k;
int L, R;

int main(){
#ifdef FILE_IO
	start;
#endif
	scanf("%d%d", &n, &k);
	for(int i = 0; i < k; i++) scanf("%*d");
	scanf("%d%d", &L, &R);
	for(int i = L; i <= R; i++) printf("0 ");
	printf("\n");
	return 0;
}