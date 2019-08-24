#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;
int a[2002], phi[1002];
int pow(int x, int k){
    int ans = 1;
    while(k){
        if(k & 1) {
            ans = ans * x % 1000;
            ans %= 1000;
        }
        x = x * x % 1000;
        k >>= 1;
    }
    return ans;
}

void phi_table(int n){
    memset(phi, 0, sizeof(phi)); phi[1] = 1;
    for(int i = 2; i <= n; i++){
        if(!phi[i]) for(int j = i; j <= n; j += i){
            if(!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
    }
}
int main(){
	freopen("20190823.1.g.txt", "w", stdout);
	a[0] = 0;
    for(int i = 1; i <= 1000; i++){
        a[i] = pow(i, i);
    }
    for(int i = 1001; i <= 2000; i++){
    	a[i] = pow(i % 1000, i % 400);
	}
	printf("{");
	for(int i = 0; i < 2000; i++){
		printf("%d,", a[i]);
	}
	printf("%d", a[2000]);
	printf("}");
    return 0;
}
