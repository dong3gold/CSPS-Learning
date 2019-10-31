#include <cstdio>
#include <algorithm>

using namespace std;
int a[102000], b[102000], c[204000], d[204000];
long long int sa, sb, p;
int n;
bool cmp(int x, int y){return c[x] < c[y];}
int main(){
	scanf("%d", &n); sa = 0;
	for(int i = 0; i < n; i++){
		scanf("%d%d", a + i, b + i);
		c[2*i] = a[i]; c[2*i+1] = b[i]; 
		d[2*i] = 2 * i; d[2*i+1]=2*i+1;
		sa += a[i];
	}
	sort(d, d + n*2, cmp);
	sb = 0;
	long long int sum, ans = 0;
	for(int i = 0; i < n*2; i++){
		if(d[i]&1){
			sum = sa + sb * c[d[i]];
			if(ans < sum){
				ans = sum;
				p = c[d[i]];
			}
			sb--;
		}
		else{
			sa -= c[d[i]], sb++;
			sum = sa + sb * c[d[i]];
			if(ans < sum){
				ans = sum;
				p = c[d[i]];
			}
		} 
	}
	printf("%d %lld\n", p, ans);
	return 0;
}
