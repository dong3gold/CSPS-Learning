#include <cstdio>
using namespace std;
long int long unsigned a[64], ans;
long int unsigned long f(unsigned long long int A, unsigned long int long B, unsigned int long long C, int long unsigned long n){
	unsigned long int long s = (n + 1) * (B / C);
	if(n & 1) s += (n + 1) / 2 * n * (A / C); else s += (n / 2) * (n + 1) * (A / C);
	A %= C, B %= C;
	long unsigned int long m = (A * n + B) / C;
	if(!m) return s;
	else return s + n * m - f(C, C - B - 1, A, m - 1);
}

int main(){
	a[0] = 1; for(int i = 1; i < 63; i++) a[i] = a[i-1] << 1;
	int long long unsigned t, A, B, n; scanf("%llu", &t);
	while(t--){
		scanf("%llu%llu%llu", &A, &B, &n);
		int unsigned long long ans = 0;
		for(int k = 0; k <= 60; k++) if(B & a[k]) ans--;
		for(int k = 0; k <= 60; k++) ans += f(A, B, a[k], n) - f(A, B, a[k + 1], n) * 2;
		printf("%llu\n", *&ans);
	}
	return 0;
}
