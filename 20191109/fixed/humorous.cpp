#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cmath>

using namespace std;

long long n;

int main(){
	//freopen("test.out", "w", stdout);
	long double C = 0.57721566490153286060651209L;
	long double sum = 0;
	scanf("%lld", &n);
	if(n <= 10000000){
		for(long long i = 1; i <= n; i++){
			sum += (long double)n / i;
		}
		printf("%lld\n", (long long)round(sum));
	}
	else{
		sum = (C + log(n)) * n + 0.5;
		printf("%lld\n", (long long)round(sum));
	}
	return 0;
}

