#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cctype>
using namespace std;

bool read(){
	char ch = 0;
	while(!isprint(ch) || ch == 32) ch = getchar();
	return ch == 'X'; 
}

int R, C; int N, M;
bool m[20][20];
int row[20][20];
bool pr[20], pn[20];
int main(){
	scanf("%d%d", &N, &M);
	memset(m, 0, sizeof(m));
	memset(row, 0, sizeof(row));
	for(int i = 1; i <= N; i++){
		for(int j = 1, tot = 1; j <= M; j++){
			m[i][j] = read();
			if(m[i][j]) row[i][tot++] = j;
		}
	}
	scanf("%d%d", &R, &C);
	int n = 1 << N; int ans = 0x7f7f7f;
	for(int i = 0; i < n; i++){
		int sum = 0; bool fl = 0;
		memset(pn, 0, sizeof(pn)); memset(pr, 0, sizeof(pr));
		for(int j = i, k = 1; k <= N; j>>=1, k++) {
			if(j & 1 && pr[k]){fl = 1; break;}
			if(j & 1){sum++; for(int l = 0; l < R; l++) pr[k+l] = 1;}
			if(!pr[k]){for(int l = 1; l <= M; l++) pn[row[k][l]] = 1;}
		}
		if(fl) continue;
		for(int j = 1; j <= M; j++){
			if(pn[j]){
				sum++;
				for(int k = 0; k < C; k++){
					pn[j+k] = 0;
				}
			}
		}
		ans = min(ans, sum);
	}
	printf("%d", ans);
	return 0;
} 
