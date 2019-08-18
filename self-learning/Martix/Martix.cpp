#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstdlib> 
using namespace std;
static const int prime = 1000000007; 
template<typename T>
struct Martix{
	T **p;
	int n, m;
	Martix<T>():n(0),m(0){p = (T**)malloc(sizeof(T));};
	Martix<T>(int n, int m):n(n),m(m){p = (T**)malloc((sizeof(T*))*n);for(int i=0;i<n;i++) p[i]=(T*)malloc(sizeof(T)*m);} 
	void adjust(int n, int m){
		this->n = n; this->m = m;
		delete(p);
		p = (T**)malloc((sizeof(T*))*n);
		for(int i=0;i<n;i++) p[i]=(T*)malloc(sizeof(T)*m);
	}
	Martix<T> operator = (const T**& x) {
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				p[i][j] = x[i][j];
			}
		}
		return *this;
	}
	Martix<T> operator = (const Martix<T>& _martix){
		adjust(_martix.n, _martix.m);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				p[i][j] = _martix.p[i][j];
			}
		}
		return *this;
	}
	T*& operator [] (const int& x){
		return this->p[x];
	}
	Martix<T> operator * (const Martix<T>& _martix){
		Martix<T> _tmp = Martix<T>(this->n, _martix.m);
		int n = this->n; int p = this->m; int m = _martix.m;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				_tmp.p[i][j] = 0;
				for(int k = 0; k < p; k++){
					_tmp.p[i][j] += (int)(((long long)(this->p[i][k]%prime) * (_martix.p[k][j] % prime)) % prime);
					_tmp.p[i][j] %= prime;
				}
			}
		}
		return _tmp; 
	}
	#ifdef stream
	friend operator << (ostream &output, const Martix<T>& _martix){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				out << this->p[i][j] << " ";
			}
			out << endl;
		}
	}
	#else
	//printfÓëÄ£°å²»¼æÈÝ£¬¿¼ÂÇÖØÔØ£¨char*£©Ëã·û 
	void print(){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				printf("%d ", p[i][j]);
			}
			printf("\n");
		}
	}
	#endif
};
Martix<int> a; int n; long long int k;
Martix<int> pow(long long int k){
	Martix<int> ans = Martix<int>(n, n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			ans[i][j] = i == j ? 1 : 0;
		}
	}
	while(k){
		if(k&1){
			ans = ans * a;
		}
		a = a * a;
		k >>= 1;
	}
	return ans;
}
int main(){
	freopen("testdata.in", "r", stdin);
	freopen("testdata.out", "w", stdout);
	scanf("%d%lld", &n, &k);
	a.adjust(n, n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			scanf("%d", &a[i][j]);
		}
	}
	pow(k).print();
	return 0;
}
