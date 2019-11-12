#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;
int mp[3100][3100];
int a[3100][3100];
int c[3100][3100];
int n, m, k;
int color[200000], cnt = 0;

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			scanf("%d", &mp[i][j]);
			if(!color[mp[i][j]])  color[mp[i][j]] = cnt++;
		}
	}
	for(int i = n - 1; i >= n - k; i--){
		for(int j = n - 1; j >= m - k; j--){
			
		}
	}
	return 0;
}