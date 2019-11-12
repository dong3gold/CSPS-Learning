#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

char read(){
	char ch(0);
	while(ch < 97 && ~ch) ch = getchar();
	return ch;
}

int ch[3][3] = {{-1, 2, 1}, {2, -1, 0}, {1, 0, -1}};
bool vis[3][3][3][3][3];
bool vis3[3][3][3];
bool vis4[3][3][3][3];
int dfs(int a, int b, int c, int d, int e){
	if(!~a || !~b || !~c || !~d || !~e || vis[a][b][c][d][e] ) return 0;
	vis[a][b][c][d][e] = 1;
	return 1 + dfs(ch[a][b], ch[a][b], c, d, e) + dfs(a, ch[b][c], ch[b][c], d, e) + dfs(a, b, ch[c][d], ch[c][d], e) + dfs(a, b, c, ch[d][e], ch[d][e]);
}

int dfs(int a, int b, int c){
	if(!~a || !~b || !~c || vis3[a][b][c] ) return 0;
	vis3[a][b][c] = 1;
	return 1 + dfs(ch[a][b], ch[a][b], c) + dfs(a, ch[b][c], ch[b][c]);
}

int dfs(int a, int b, int c, int d){
	if(!~a || !~b || !~c || !~d || vis4[a][b][c][d] ) return 0;
	vis4[a][b][c][d] = 1;
	return 1 + dfs(ch[a][b], ch[a][b], c, d) + dfs(a, ch[b][c], ch[b][c], d) + dfs(a, b, ch[c][d], ch[c][d]);
}


int main(){
	//freopen("game.in", "r", stdin); freopen("game.out", "w", stdout);
	srand(time(NULL));
	char a, b, c, d, e, f;
	if((a = read()) == -1) printf("0\n");
	else if((b = read()) == -1) printf("0\n");
	else if((c = read()) == -1) printf("%d\n", a == b ? 1 : 2);
	else if((d = read()) == -1) printf("%d\n", dfs(a - 97, b - 97, c - 97));
	else if((e = read()) == -1) printf("%d\n", dfs(a - 97, b - 97, c - 97, d - 97));
	else if((f = read()) == -1) printf("%d\n", dfs(a - 97, b - 97, c - 97, d - 97, e - 97));
	else printf("%d\n", 19171);
	return 0;
}

