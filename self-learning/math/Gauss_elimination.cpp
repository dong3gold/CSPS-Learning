#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;
static const long double eps = 1e-7;
long double **p; int n;

void adjust(int n, int m){
	p = (long double**) malloc(sizeof(long double*) * n);
	for(int i = 0; i < n; i++){
		p[i] = (long double*) malloc(sizeof(long double) * m);
	}
}

bool Gauss(long double **A, int n){
	for(int i = 0; i < n; i++){
		int r = i;
		for(int j = i + 1; j < n; j++){
			if(fabs(A[j][i]) > fabs(A[r][i])) r = j;
		}
		if(fabs(A[r][i]) < eps) {
			printf("No Solution\n");
			return 1;
		}
		if(r != i) swap(A[r], A[i]);
		for(int k = i + 1; k < n; k++){
			long double f = A[k][i] / A[i][i];
			for(int j = i; j <= n; j++) A[k][j] -= f * A[i][j];
		}
	}
	
	for(int i = n - 1; i >= 0; i--){
		for(int j = i + 1; j < n; j++){
			A[i][n] -= A[j][n] * A[i][j];
		} 
		A[i][n] /= A[i][i];
	}
	return 0;
}

int main(){
	scanf("%d", &n);
	adjust(n, n+1);
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= n; j++){
			scanf("%Lf", p[i] + j);
		}
	}
	bool a = Gauss(p, n);
	for(int i = 0; i < n && !a; i++){
		printf("%.2Lf\n", p[i][n]);
	}
	return 0;
}
