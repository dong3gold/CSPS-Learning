#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
using namespace std;

int read(){
	char ch = 0; int X = 0;
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) {X = (X << 3) + (X << 1) + (ch ^ 48); ch = getchar();}
	return X;
}
const int a[101] = {0, 0, 2, 0, 2, 0, 4, 0, 10, 0, 28, 0, 84, 0, 264, 0, 858, 0, 2860, 0, 9724, 0, 33592, 0, 117572, 0, 416024, 0, 1485800, 0, 5348880, 0, 19389690, 0, 70715340, 0, 259289580, 0, 955277400, 0, 534526359, 0, 128240749, 0, 932533704, 0, 965126006, 0, 119222498, 0, 808276595, 0, 892734843, 0, 705887166, 0, 100858539, 0, 899808255, 0, 419271348, 0, 950774804, 0, 874828921, 0, 976619500, 0, 851780421, 0, 918245024, 0, 186605902, 0, 283730756, 0, 932228693, 0, 739341107, 0, 996463249, 0, 205882739, 0, 936976280, 0, 872978178, 0, 9233846, 0, 769037543, 0, 410623518, 0, 675180425, 0, 491324132, 0, 435746624, 0, 530696893}; 
long long p[10000001];

int main(){
	int n = read(), m = read();
	p[0] = 1; p[1] = 0; p[2] = 2;
	for(int i = 3; i <= n; i++){
		p[i] = 0;
		for(int j = 1; j <= min(i, m); j++){
			p[i] += p[i - j] * a[j] % 1000000007;
			p[i] %= 1000000007;
		}
	}
	printf("%lld\n", p[n]);
	return 0;
}