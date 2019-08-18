#include <cstdio>
#include <algorithm>
#include <queue>
#include <cctype>
using namespace std;

int d[400][400];
vector<int> G[400];
int n, m;

int read(){
	int X = 0, w = 0; char ch = 0;
	while(!isdigit(ch)){w|=ch=='-';ch = getchar();} 
	while(isdigit(ch)){X = (X<<1)+(X<<3)+(ch^48);ch=getchar();}
	return w ? -X : X;
}

void addEdge(int score, int to, int from){
	G[from].push_back(to);
}

void Dp(int u){
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		Dp(v);
		for(int j = m+1; j > 0; j--){
			for(int k = 0; k < j; k++){
				d[u][j] = max(d[u][j], d[u][j - k - 1] + d[v][k]);
			}
		}
	}
}

int main(){
	n = read(); m = read();
	d[0][0] = 0;
	for(int i = 1; i <= n; i++){
		addEdge(d[i][0] = read(), i, read());
	}
	Dp(0);
	printf("%d", d[0][m]);
	return 0;
}
