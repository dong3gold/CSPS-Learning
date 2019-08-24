#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
using namespace std;

int read() {
	char ch = 0; int X = 0;
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) { X = (X << 3) + (X << 1) + (ch ^ 48); ch = getchar(); }
	return X;
}
int n, m;
const int a[101] = { 0, 0, 2, 0, 2, 0, 4, 0, 10, 0, 28, 0, 84, 0, 264, 0, 858, 0, 2860, 0, 9724, 0, 33592, 0, 117572, 0, 416024, 0, 1485800, 0, 5348880, 0, 19389690, 0, 70715340, 0, 259289580, 0, 955277400, 0, 534526359, 0, 128240749, 0, 932533704, 0, 965126006, 0, 119222498, 0, 808276595, 0, 892734843, 0, 705887166, 0, 100858539, 0, 899808255, 0, 419271348, 0, 950774804, 0, 874828921, 0, 976619500, 0, 851780421, 0, 918245024, 0, 186605902, 0, 283730756, 0, 932228693, 0, 739341107, 0, 996463249, 0, 205882739, 0, 936976280, 0, 872978178, 0, 9233846, 0, 769037543, 0, 410623518, 0, 675180425, 0, 491324132, 0, 435746624, 0, 530696893 };
static const int prime = 1000000007;
long long p[10000001];
template<typename T>
struct Martix {
	T** p;
	int n, m;
	Martix<T>() : n(0), m(0) { p = (T * *)malloc(sizeof(T)); };
	Martix<T>(int n, int m) : n(n), m(m) { p = (T * *)malloc((sizeof(T*)) * n); for (int i = 0; i < n; i++) p[i] = (T*)malloc(sizeof(T) * m); }
	void adjust(int n, int m) {
		this->n = n; this->m = m;
		delete(p);
		p = (T * *)malloc((sizeof(T*)) * n);
		for (int i = 0; i < n; i++) p[i] = (T*)malloc(sizeof(T) * m);
	}
	Martix<T> operator = (const T**& x) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				p[i][j] = x[i][j];
			}
		}
		return *this;
	}
	Martix<T> operator = (const Martix<T>& _martix) {
		adjust(_martix.n, _martix.m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				p[i][j] = _martix.p[i][j];
			}
		}
		return *this;
	}
	T*& operator [] (const int& x) {
		return this->p[x];
	}
	template<typename T2>
	Martix<T2> operator * (const Martix<T2>& _martix) {
		Martix<T2> _tmp(this->n, _martix.m);
		int n = this->n; int p = this->m; int m = _martix.m;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				_tmp.p[i][j] = 0;
				for (int k = 0; k < p; k++) {
					_tmp.p[i][j] += (((T)(this->p[i][k] % prime) * (_martix.p[k][j] % prime)) % prime);
					_tmp.p[i][j] %= prime;
				}
			}
		}
		return _tmp;
	}
	void print() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%d ", p[i][j]);
			}
			printf("\n");
		}
	}
};
Martix<long long> A;
Martix<long long> F;
Martix<long long> pow_mul(long long t) {
	Martix<long long> ans(m, m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			ans[i][j] = i == j;
		}
	}
	while (t) {
		if (t & 1) {
			ans = ans * A;
		}
		A = A * A;
		t >>= 1;
	}
	return ans;
}



int main(){
	n = read(), m = read();
	A.adjust(m, m); F.adjust(m, 1);
	p[0] = 1; p[1] = 0; p[2] = 2; F[0][0] = 0; F[1][0] = 2;
	for (int i = 0; i < m - 1; i++) {
		for(int j = 0; j < m; j++){
			A[i][j] = j == i + 1;
		}
	}
	for(int i = 0; i < m; i++){
		A[m-1][m-i-1] = a[i+1];
	}
	for (int i = 3; i <= m; i++) {
		p[i] = 0;
		for (int j = 1; j <= i; j++) {
			p[i] += p[i - j] * a[j] % 1000000007;
			p[i] %= 1000000007;
		}
		F[i - 1][0] = p[i];
	}
	if(n > m){
		printf("%lld\n", (pow_mul(n - m) * F)[m - 1][0]);
	}
	else printf("%lld\n", p[n]);
	return 0;
}
