#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int GCD(int x, int y){return y ? GCD(y, x %y) : x;}

template<typename T, int n, int m>
struct Martix{
	T **p;
	Martix<T, n, m>(){p = (T**)malloc((sizeof(T*))*n);for(int i=0;i<n;i++) p[i]=(T*)malloc(sizeof(T)*m);};
	Martix<T, n, m> operator = (const T**& x) {
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				p[i][j] = x[i][j];
			}
		}
		return *this;
	}
	Martix<T, n, m> operator = (const Martix<T, n, m>& _martix){
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
	
	template<typename T2, int n2,int m2>
	Martix<T, n, m2> operator * (const Martix<T2, n2, m2>& _martix){
		Martix<T, n, m2> _tmp;
		int p = n2;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				_tmp.p[i][j] = 0;
				for(int k = 0; k < p; k++){
					_tmp.p[i][j] += this->p[i][k] * _martix.p[k][j];
				}
			}
		}
		return _tmp; 
	}
	template<typename T2, int n2,int m2>
	Martix<T, n, m2> operator *= (const Martix<T2, n2, m2>& _martix) {
		*this = *this*_martix; return *this;
	}
};
Martix<double, 2, 2> M;
Martix<double, 2, 1> vec[200200];
Martix<int, 2, 1> rvec[200200];
Martix<int, 2, 1> make_vector(int x, int y){ Martix<int, 2, 1> t; t[0][0] = x;t[1][0] = y; return t;}

int id[200200];
bool cmp(int x, int y){return vec[x][0][0] < vec[y][0][0];}

double slope(Martix<double, 2, 1> a, Martix<double, 2, 1> b){
	return (b[1][0] - a[1][0]) / (b[0][0] - a[0][0]); 
}
int main(){
	freopen("slope.in", "r", stdin);
	freopen("slope.out", "w", stdout);
	int n, x, y, p, q;
	scanf("%d%d%d", &n, &p, &q);
	double k = atan((double)p/q);
	M[0][0] = sin(k), M[0][1] = -cos(k); M[1][0] = cos(k); M[1][1] = sin(k);
	for(int i = 0; i < n; i++){
		scanf("%d%d", &x, &y);
		rvec[i] = make_vector(x, y);
		vec[i][0][0] = rvec[i][0][0];
		vec[i][1][0] = rvec[i][1][0];
		vec[i] = M * vec[i];
		id[i] = i;
	}
	sort(id, id+n, cmp);
	double ansSlope = 0; int ansp = 0, ansq = 0;
	double slp = 0;
	for(int i = 0; i < n - 1; i++){
		if((slp = abs(slope(vec[id[i]], vec[id[i+1]])))> ansSlope){
			ansSlope = slp;
			ansp = abs(rvec[id[i+1]][1][0] - rvec[id[i]][1][0]);
			ansq = abs(rvec[id[i+1]][0][0] - rvec[id[i]][0][0]);
		}
	}
	printf("%d/%d", ansp / GCD(ansp, ansq), ansq / GCD(ansp, ansq));
	return 0;
}
