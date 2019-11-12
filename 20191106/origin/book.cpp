#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>

using namespace std;

void exgcd(long long a, long long b, long long &d, long long &x, long long &y){
	if(!b) {d = a; x = 1; y = 0;}
	else {exgcd(b, a % b, d, y, x); y -= a / b * x;}
}

long long N, X, A, B, M;
long long x, y, d;
long long sum;

int main(){
	scanf("%lld%lld%lld%lld%lld", &N, &X, &A, &B, &M);
	sum = (N - 1) & 1 ? (N-2)/2 * (N-1) : (N-1)/2 * (N-2);
	exgcd(A, B, d, x, y);
	x *= (M - N * X) / d; y *= - ((M - N * X) / d);
	while(x + y < sum) x+=B, y+=A;
	while(x + y > sum) x-=B, y-=A;
	printf("%lld ", X);
	for(int i = 1, j = 1; i <= x; i+=j, j++){
		printf("%lld ", X += A);
	}
	for(int i = 1, j = 1; i <= y; i+=j, j++){
		printf("%lld ", X -= B);
	}
	return 0;
}