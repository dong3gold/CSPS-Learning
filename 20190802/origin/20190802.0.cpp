#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <stack>
using namespace std;

int choice = 1;
int bitter[12], sour[12];
int sumB, sumS;
inline int absDif(int a, int b){
	return a >= b ? a - b : b - a;
}
int main(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d%d", sour + i, bitter + i);
	}
	bitter[11] = 0;
	sour[11] = 1; 
	int mx = 1 << n; int mn = 0x4fffffff;
	for(;choice < mx; choice++){
		sumB = 0; sumS = 1;
		for(int i = 0; i < n; i++){
			sumB += bitter[(choice & (1 << i)) ? i : 11];
			sumS *= sour[(choice & (1 << i)) ? i : 11];
		}
		mn = min(mn, absDif(sumB, sumS));
	}
	printf("%d\n", mn);
}
