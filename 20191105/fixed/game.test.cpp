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

bool vis4[3][3][3][3];

int dfs(int a, int b, int c, int d){
	if(!~a || !~b || !~c || !~d || vis4[a][b][c][d] ) return 0;
	vis4[a][b][c][d] = 1;
	return 1 + dfs(ch[a][b], ch[a][b], c, d) + dfs(a, ch[b][c], ch[b][c], d) + dfs(a, b, ch[c][d], ch[c][d]);
}


int main(){
	//freopen("game.in", "r", stdin); freopen("game.out", "w", stdout);
	srand(time(NULL));
	char a, b, c, d, e, f;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			for(int k = 0; k < 3; k++){
				for(int m = 0; m < 3; m++){
					printf("%c%c%c%c:%d\n",i + 97, j + 97, k + 97, m + 97, dfs(i, j, k, m));
					memset(vis4, 0, sizeof(vis4));
				}
			}
		}
	}
	return 0;
}

