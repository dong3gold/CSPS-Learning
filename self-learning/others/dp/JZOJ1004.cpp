#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;
bool a[85][85];
bool f[85][85];
int n;
int read(){
	int X = 0, w = 0; char ch = 0;
	while(!isdigit(ch)){w|=ch=='-';ch = getchar();} 
	while(isdigit(ch)){X = (X<<1)+(X<<3)+(ch^48);ch=getchar();}
	return w ? -X : X;
}
int main(){
	n = read();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			a[i+n][j+n] = a[i+n][j] = a[i][j+n] = a[i][j] = read();
		}
		f[i][i+1] = f[i+n][i+n+1] = 1;
	}
	for(int i = 2*n-3; i >= 0; i--){
		for(int j = i + 2; j < 2*n; j++){
			for(int k = i+1; k < j; k++){
				f[i][j] |= (f[i][k] && f[k][j] && (a[i][k] || a[j][k]));
			}
		}
	}
	for(int i = 0; i < n; i++){
		printf("%d\n", f[i][i+n]);
	}
	return 0;
}
