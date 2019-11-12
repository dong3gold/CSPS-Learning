#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;
long long int a, sum;

int main(){
	while(~scanf("%lld", &a)) sum += a;
	printf("%lld", sum);
	return 0;
}

