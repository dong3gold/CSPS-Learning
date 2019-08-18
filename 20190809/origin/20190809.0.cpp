#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cstdlib>

using namespace std;
int n, m, t;
bool a[60][60];
int d[3600][2500];
int read(){
	int X = 0, w = 0; char ch = 0;
	while(!isdigit(ch)){w|=ch=='-';ch = getchar();} 
	while(isdigit(ch)){X = (X<<1)+(X<<3)+(ch^48);ch=getchar();}
	return w ? -X : X;
}
vector<int> G[3600]; int _x = 0;
void addEdge(int from, int to){
	G[form].push_back(to);
}
vector<int> f[60];

int main(){
	n = read(); m = read(); t = read();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			a[i][j] = read();
		}
	}
	for(int i = 0; i < n; i++){
		int cnt = 0; w = a[i][0];
		for(int j = 0; j < m; j++){
			if(w == a[i][j]) cnt++;
			else{
				d[_x++][0] = cnt;
				w = a[i][j];
				cnt = 1;
			}
		}
	}
	return 0;
}
