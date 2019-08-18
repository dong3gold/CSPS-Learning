#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
using namespace std;

int read(){
	char ch = 0; int X = 0;
	while(!isdigit(ch)){ch = getchar();}
	while(isdigit(ch)){X=(X << 3)+(X << 1)+(ch^48); ch=getchar();}
	return X;
}

int a[100020];
int main(){
	int n, k; memset(a, 0, sizeof(a));
	n = read(); k = read();
	for(int i = 0; i < n; i++){
		a[read()]++;
	}
	int p = 0, i;
	for(i = 0; p < k; i++){
		for(int j = 0; j < a[i] && p < k; j++){
			p++; printf("%d ", i);
		}
	}
	printf("\n");
}
