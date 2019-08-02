#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>

using namespace std;
int n;
bool a[101];
bool b[101];
int tot = 0;
int sm = 0;
bool readOdd(){
	bool X; char ch = 0;
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)){
		X = ch & 1;
		ch = getchar();
	}
	tot += X;
	return X;
}
bool dfs(int j, int k, bool isAlice, int sumA, int sumB){
	if(sumA > tot/2) return isAlice;
	if(sumB >= tot/2) return isAlice^1;
	if(j < k - 1){
		return !(dfs(j + 1, k, isAlice^1, sumA + b[j]*isAlice, sumB + b[j]*isAlice) && dfs(j, k - 1, isAlice^1, sumA + b[k]*isAlice, sumB + b[k]*isAlice));
	}
	return isAlice^1;
}

bool init(int c){
	for(int i = 0; i < n - c - 1; i++){
		b[i] = a[c + i + 1];
	}
	for(int i = n - c - 1; i < n - 1; i++){
		b[i] = a[n - i - 2];
	}
	return dfs(0, n - 1, 1, a[c], 0);
}
int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		a[i] = readOdd();
	}
	for(int i = 0; i < n; i++){
		sm += init(i);
	}
	printf("%d", sm);
	return 0;
}
