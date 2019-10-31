#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int DEF[100020], tot1 = 0;
int ATK[100020], tot2 = 0;
int X[100020], x[100020], tot3 = 0;
int Y[100020], tot4;
bool nonDEF = 1;

int n, m;

void readCard(){
	char ch[3]; int atk;
	scanf("%s%d", ch, &atk);
	if(ch[0] == 'A') ATK[tot2++] = atk;
	else {
		DEF[tot1++] = atk;
		nonDEF = 0;
	}
	Y[tot4++] = atk;
}
void shuffle(){
	sort(DEF, DEF + tot1);
	sort(ATK, ATK + tot2);
	sort(X, X + m);
	sort(Y, Y + n);
}

long long int work1(){
	long long int sum = 0;
	for(int i = m - 1, j = 0; i >= 0 && j < tot2; ){
		if(X[i] <= ATK[j]) break;
		sum += X[i--] - ATK[j++];
	}
	return sum;
}
long long int work2(){
	long long int sum = 0; int i = 0, j = 0;
	int ed = m - 1;
	while(j < tot1){
		auto low = upper_bound(X + i, X + ed, DEF[j]);
		*low = 0;
		i = low - X + 1;
		DEF[j++] = 0;
	}
	for(i = 0; i < m; i++){
		sum+=X[i];
	}
	for(j = 0; j < tot2; j++){
		sum-=ATK[j];
	}
	return sum;
}
int main(){
	scanf("%d%d", &n, &m);
	memset(DEF, 0, sizeof(DEF));
	memset(ATK, 0, sizeof(ATK));
	for(int i = 0; i < n; i++){
		::readCard();
	}
	for(int i = 0; i < m; i++){
		scanf("%d", X+i);
	}
	shuffle();
	if(m <= n){
		printf("%lld\n", work1()); return 0;
	}
	else{
		int i = m - 1, j = n - 1;
		while(j >= 0){
			if(X[i--] < Y[j--]) {
				printf("%lld\n", work1()); return 0;
			}
		}
		long long a = work1();
		long long b = work2();
		printf("%lld\n", max(a, b));
	}
	return 0;
}
