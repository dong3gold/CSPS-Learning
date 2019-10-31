#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <stack>
#include <cstring>
#include <assert.h>
using namespace std;
int tot = 1;
int c[6] = {0x7f7f7f,1,0,0,0,0};

struct Hex{
	int value;
	int edge[6];
	int head;
	Hex(){value = -1; head = 0;memset(edge, 0, sizeof(edge));}
}hex[12300];
bool near(Hex a, int x){
	for(int i = 0; i < 6; i++){
		if(hex[a.edge[i]].value == x) return true;
	}
	return false;
}
void addEdge(int a, int b, int pos){
	hex[a].edge[pos] = b;
	hex[b].edge[(pos+3)%6] = a;
	hex[b].head = (pos + 4) % 6; 
}
void work(){
	for(int now = 1; now < 10010; now++){
		int start = hex[now].head, end = start + 6;
		for(int i = start; i < end; i++){
			if(hex[now].edge[i%6] == 0) addEdge(now, ++tot, i%6);
		}
		for(int i = start; i < end; i++){
			if(hex[hex[now].edge[i%6]].edge[(i+2)%6] == 0) 
				addEdge(hex[now].edge[i%6], hex[now].edge[(i+1)%6], (i+2)%6);
		}	
	}
}
void color(){
	hex[1].value = 1;
	for(int i = 2; i < 10010; i++){
		int min = 0;
		for(int j = 1; j < 6; j++){
			if(c[j] < c[min] && !near(hex[i], j)){
				min = j;
			}
		}
		hex[i].value = min; c[min]++;
	}
}
int main(){
	int T, n;
	work();
	color();
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		printf("%d\n", hex[n].value);
	}
	return 0;
}
