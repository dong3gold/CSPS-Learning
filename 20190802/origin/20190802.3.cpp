#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <stack>
using namespace std;
struct seg{
	int a, b;
	seg():a(0), b(0){}
	seg(int A, int B):a(A), b(B){}
	bool operator <(const seg& x) const{
		return x.b == b ? x.a > a : x.b < b; 
	}
}segs[10010];
int main(){
	int n, A, B, tot = 0, right = 10000000, left = -1;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d%d", &A, &B);
		segs[i] = seg(A,B);
	}
	sort(segs, segs+n);
	for(int i = 0; i < n; i++){
		if(segs[i].b <= right){
			if(segs[i].a >= left){
				tot++; right = segs[i].b; left = segs[i].a;
			}
		}
	}
	printf("%d\n", tot);
	return 0;
}
