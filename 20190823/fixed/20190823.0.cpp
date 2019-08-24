#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;
inline int read(){
	int X = 0; char ch = 0;
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) {X = (X<<3) + (X<<1) + (ch^48); ch = getchar();}
	return X;
}
double a[1025][1025], w[1025][11];
int main(){
	int n;
	n = read(); int m = 1 << n;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < m; j++){
			a[i][j] = static_cast<double>(read()) / 100;
		}
	}
	for(int i = 0; i < m; i++) w[i][0] = a[i][i^1];
	for(int i = 1; i < n; i++){
		int p = 1 << i;
		for(int j = 0; j < m; j++){
			int s = (j & (-p)) ^ p;
			w[j][i] = 0;
			for(int k = 0; k < p; k++){
				w[j][i] += w[s+k][i-1] * a[j][s+k]; 
			}
			w[j][i] *= w[j][i-1];
		}
	}
	int ans = 0;
	for(int i = 1; i < m; i++){
		if(w[i][n-1] > w[ans][n-1]) ans = i;
	}
	printf("%d\n", ans+1);
    return 0;
}
