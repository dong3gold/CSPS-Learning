#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <stack>

using namespace std;

char ss[500050];
long long ans = 0;
long long endb = 0;
int main(){
	freopen("replace.in", "r", stdin); freopen("replace.out", "w", stdout);
	scanf("%s", ss);
	int r = strlen(ss);
	int l = 0;
	for(; l < r; l++){
		if(ss[l] == 'a') break;
	}
	for(;r > l; r--){
		if(ss[r - 1] == 'b') break;
	}
	for(int i = r - 1; i >= l; i--){
		if(ss[i] == 'a'){ans += endb; endb *= 2;}
		else endb++;
		ans %= 1000000007;
		endb %= 1000000007;
	}
	printf("%d\n", ans);
	return 0;
}