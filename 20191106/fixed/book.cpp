#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>

using namespace std;

long long N, X, A, B, M;
long long x, y, d;
long long sum;

int main(){
	//freopen("book.out", "w", stdout);
	scanf("%lld%lld%lld%lld%lld", &N, &X, &A, &B, &M);
	sum = (N-1) * N / 2;
	x = (M - N * X + sum * B) / (A + B);
	y = sum - x;
	printf("%lld ", X);
	if(N == 1) return 0;
	int i = 1;
	for(; x >= N - i; x -= N - i, i++) 
		printf("%lld ", X += A);
	for(; y && x != N - i; y -= N - i, i++) 
		printf("%lld ", X -= B);
	if(x != 0)printf("%lld ", X += A); i++;
	for(; i < N; y -= N - i, i++) printf("%lld ", X -= B);
	return 0;
}
