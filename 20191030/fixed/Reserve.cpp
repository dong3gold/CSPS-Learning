#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;

int a[100020];
int n;

template<int N>
struct fwkTree{
	int c[N];
	fwkTree(){memset(c, 0, sizeof(c));}
	
	#define lowbit(x) (x&-x)
	void update(int x){ for(;x;x-=lowbit(x)) c[x]++;}
	int query(int x) {int ans = 0; for(;x<N;x+=lowbit(x)) ans += c[x]; return ans;}
	#undef lowbit
};

fwkTree<100020> tr;

long long count_rev(){ long long ans = 0;
	for(int i = 1; i <= n; i++){
		ans += tr.query(a[i]);
		tr.update(a[i]);
	}
	return ans;
}

void rev(int l, int r){
	for(int i = l, j = r; i < j; i++, j--){swap(a[i], a[j]);}
}
long long ans = 0; bool done = 0;
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	int cnt = 0; done = 1;
	for(int i = 1; i < n; i++){
		if(a[i] > a[i + 1]) cnt++, done = 0;
		else if(cnt){
			rev(i - cnt, i); ans++; cnt = 0;
		}
	}
	if(cnt) rev(n - cnt, n), ans++;
	printf("%lld\n", ans += count_rev());
	return 0;
}

