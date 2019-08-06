#include <cstdio>
#include <algorithm>
using namespace std;
int a[2000500];
int st, ed;

void work(int x){
	int i = st - x;int tmp = 0;
	for(; i+x<=ed; i+=x){
		swap(a[i+x], tmp);
	}
	if(i<ed){
		swap(a[ed], tmp);
	}
	++ed; ++st;
}
int main(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		a[i] = i+1;
	}
	ed = n; st = 0;
	for(int i = 2; i <= n; i++){
		work(i);
	}
	for(int i = st; i < ed; i++){
		printf("%d ", a[i]);
	}
	return 0;
}
