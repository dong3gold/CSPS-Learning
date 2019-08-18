#include <cstdio>
#include <algorithm>
using namespace std;
int n;
double f[1<<20],a[25][25];
int main()
{
	scanf("%d", &n);
	for(int i = 1;i <= n; i++){
		for(int j = 1;j <= n; j++){
	 		scanf("%lf", a[i] + j);	
		}
	}
	for(int i = 1; i <= n; i++){
		f[1 << (i - 1)] = a[1][i];
	}
	for(int i = 1;i < (1 << n); i++){
	  int t = 0;
	  for(int j = i; j ;j -= (j & -j), t++);
	  for(int j = 0; j < n; j++)
	   if(i & (1 << j))
	    f[i] = max(f[i], f[i ^ (1 << j)] * a[t][j + 1] / 100);
	}
	printf("%0.6lf",f[(1<<n)-1]);
}
