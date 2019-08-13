#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;
int read(){
	int X = 0, w = 0; char ch = 0;
	while(!isdigit(ch)){w |= ch == '-'; ch = getchar();}
	while(isdigit(ch)){X = (X<<3) + (X<<1) + (ch^48); ch = getchar();}
	return w ? -X : X;
}
int n, head, tail, f[100020];
int pre[100020], next[100020];
int main(){
    n = read(); head = 1; tail = n;
    for(int i = 1; i <= n; i++){
        f[read()] = i;
        next[i] = i + 1; pre[i] = i - 1;
    }
    int l = 1, r = n, sum; int head = 1, tail = n;
    while(l <= r){
        int i = f[l++]; sum = 0;
        while(i>head) sum++, i = pre[i];
        printf("%d\n", sum);
        if(f[l - 1] == head) head = next[f[l-1]];
        else if(f[l - 1] == tail) tail = pre[f[l-1]];
        else pre[next[f[l-1]]] = pre[f[l-1]], next[pre[f[l-1]]] = next[f[l-1]];
        if(l<=r){
        	int j = f[r--]; sum = 0;
        	while(j < tail) sum++, j = next[j];
        	printf("%d\n", sum);
        	if(f[r + 1] == head) head = next[f[r+1]];
        	else if(f[r+1] == tail) tail = pre[f[r+1]];
        	else pre[next[f[r+1]]] = pre[f[r+1]], next[pre[f[r+1]]] = next[f[r+1]];
		}
    }
}
