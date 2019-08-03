#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#define lowbit(x) (x&-x)

using namespace std;
struct seg{
	int a, b;
	seg(){}
	seg(int A, int B):a(A),b(B){}
	bool operator < (const seg& x) const{
		return b == x.b ? a < x.a : b > x.b;
	}
}segs[100020];
/*
int read(){
	int X = 0, w = 0; char ch =0;
	while(!isdigit(ch)){w=ch=='-';ch=getchar();}
	while(isdigit(ch)){
		X = (X<<3) + (X<<1) + (ch^48);
		ch = getchar();
	}
	return w ? -X : X;
}
*/
int c[1000020];
int big = 0;
void upd(int x, int y){
	for(; x <= big ;x += lowbit(x)){
		c[x] = max(c[x], y);
	}
}

int ask(int x){
	int r = c[x];
	for(; x; x -= lowbit(x)){
		r = max(r, c[x]);
	}
	return r;
}

int main(){
	int n; int ans;int A, B;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &A, &B);
		segs[i] = seg(A, B);
		big = max(big, segs[i].a);
	}sort(segs+1, segs+1+n);
	
	for(int i = 1; i <= n; i++){
		int x = ask(segs[i].a) + 1;
		ans = max(ans, x);
		upd(segs[i].a, x);
	}
	printf("%d\n", ans);
	return 0;
}

