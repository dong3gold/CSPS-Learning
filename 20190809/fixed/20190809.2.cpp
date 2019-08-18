#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstdlib> 
#include <cstring>
using namespace std;
static const int prime = 2009; 
int read(){
	char ch = 0;
	while(!isdigit(ch)){ch = getchar();} 
	return ch^48;
}
template<typename T>
struct Martix{
	T **p;
	int n, m;
	Martix<T>():n(0),m(0){p = (T**)malloc(sizeof(T));};
	Martix<T>(int n, int m):n(n),m(m){p = (T**)malloc((sizeof(T*))*n);for(int i=0;i<m;i++) p[i]=(T*)malloc(sizeof(T)*m);} 
	void adjust(int n, int m){
		this->n = n; this->m = m;
		delete(p);
		p = (T**)malloc((sizeof(T*))*n);
		for(int i=0;i<m;i++) p[i]=(T*)malloc(sizeof(T)*m);
	}
	Martix<T> operator = (T* x) {
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				p[i][j] = x[i*100 + j];
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
					_tmp.p[i][j] += (T)(((long long)(this->p[i][k]%prime) * (_martix.p[k][j] % prime)) % prime);
					_tmp.p[i][j] %= prime;
				}
			}
		}
		return _tmp; 
	}
	Martix<T> pow(long long int k){
		Martix<T> ans = Martix<T>(n, n);
		Martix<T> a = *this;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				ans[i][j] = i == j ? 1 : 0;
			}
		}
		while(k){
			if(k&1){
				ans = ans * (a);
			}
			a = a*a;
			k >>= 1;
		}
		return ans;
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

int tmp, n, t;
Martix<int> w;
int m[100][100]; int ex[10][10], tot = 0;

int main(){
	scanf("%d%d", &n, &t);
	memset(m, 0, sizeof(m));
	memset(ex, 0, sizeof(ex));
	tot = n;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			tmp = read();
			if(tmp > 1){
				if(!ex[i][tmp-1]){
					ex[i][0] = i;
					for(int k = 1; k < tmp; k++){
						if(!ex[i][k]){
							ex[i][k] = tot++;
							m[ex[i][k-1]][ex[i][k]] = 1;
						}
					}
				}
				m[ex[i][tmp-1]][j] = 1;
			}
			else{
				m[i][j] = tmp;
			}
		}
	}
	w.adjust(tot, tot);
	w = (int *) m;
	//w.print();
	//printf("\n");
	printf("%d\n", w.pow(t).operator [](0)[n-1]);
	return 0;
}
