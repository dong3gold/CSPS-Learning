#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;
int p[2020][2020];
bool room[2020][2020];

bool read(){
	char ch = 0;
	while(!isprint(ch) || ch == 32){ch = getchar();} 
	return ch == 'X' ? 0 : 1;
}

int main(){	
	memset(p, 0, sizeof(p));
	memset(room, 0 , sizeof(room));
	int n, m;
	int ans = 0;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			room[i][j] = read();
			p[i][j] = room[i][j] ? i ? p[i-1][j] + 1 : 1 : 0;
		}
	}
	for(int x = 0; x < n; x++){
		for(int y = 0; y < m; y++){
			if(room[x][y]){
				int wide = 0, height = 0x7f7f7f;
				for(int k = y; k < m; k++){
					if(room[x][k]){
						wide++; height = min(height, p[x][k]);
						ans = max(ans, 2*(wide+height));
					}
					else break;
				}
			}
		}
	}
	printf("%d\n", ans - 1);
	return 0;
}
