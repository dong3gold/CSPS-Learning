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
int a[510][510], mx[510][510];
int main(){
    int n = read();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            a[i][j] = read();
        }
    }
    for(int i = 0; i < n; i++){
        a[i][n] = 0;
        a[n][i] = 0;
    }
    for(int i = n - 1; i >= 0; i--){
        for(int j = n - 1; j >= 0; j--){
            mn[i][j] = min(a[i][j], max(mx[i+1][j], mx[i][j+1]));
        }
    }
    return 0;
}
