#include <cstdio>
#include <algorithm>
using namespace std;
int phi[500000];
int prime[500000], tot = 1;
void phi_table(int n){
	phi[1] = 1;
	for(int i = 2; i < n; i++){
		if(!phi[i]){
			prime[tot++] = i;
			for(int j = i; j < n; j+=i){
				if(!phi[j]) phi[j] = j;
				phi[j] = phi[j] / i * (i-1); 	
			}
		}
	}
}
int main(){
	freopen("prime.txt", "w", stdout);
	phi_table(490000);
	for(int i = 1; prime[i]; i++){
		printf("%d,", prime[i]);
	}
	return 0;
}
