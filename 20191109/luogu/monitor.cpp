#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cmath>

using namespace std;
bool m[1000001]; int n;
int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", m + i);
	}
	int t = 0, i = 0;
	while(i < n){
		while(i < n && !(m[i] ^ (t & 1))) 
			i++;
		t++;
	}
	printf("%d", t);
	return 0;
}