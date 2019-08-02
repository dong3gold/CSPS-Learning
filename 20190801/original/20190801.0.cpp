#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>

using namespace std;
int n;
bool readOdd(){
	bool X; char ch = 0;
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)){
		X = ch & 1;
		ch = getchar();
	}
	return X;
}
bool a[1002][1002];
bool h[1002][1002], l[1002][1002];

void sum(){
	for(int j = 0; j < n; j++) l[0][j] = a[0][j];
	for(int i = 0; i < n; i++) h[i][0] = a[i][0];
	for(int i = 1; i < n; i++){
		for(int j = 0; j < n; j++){
			l[i][j] = l[i - 1][j] ^ a[i][j];
		}
	} 
	for(int j = 1; j < n; j++){
		for(int i = 0; i < n; i++){
			h[i][j] = h[i][j - 1] ^ a[i][j];
		}
	}
	return ;
}

bool dfs(int x, int y){
	if(x < 0 || y < 0 || (l[y][x] && h[y][x])) 
		return 0;
	if(l[y][x]){
		return dfs(x, y - 1) ^ 1;
	}
	if(h[y][x]){
		return dfs(x - 1, y) ^ 1;
	}
	return (dfs(x-1, y) ^ 1) || (dfs(x, y - 1) ^ 1);
}

char W[2] = {'L', 'W'};
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				a[i][j] = readOdd();
			}
		}
		sum();
		printf("%c\n", W[dfs(n - 1, n - 1)]);
	}
	return 0;
}
