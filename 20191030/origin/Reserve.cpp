#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;

int a[100020];
int n;

void rev(int l, int r){
	for(int i = l, j = r; i < j; i++, j--){swap(a[i], a[j]);}
}
int ans = 0; bool done = 0;
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	while(!done){
		int cnt = 0; done = 1;
		for(int i = 1; i < n; i++){
			if(a[i] > a[i + 1]) cnt++, done = 0;
			else if(cnt){
				rev(i - cnt, i); ans++; cnt = 0;
			}
		}
		if(cnt) rev(n - cnt, n), ans++;
	}
	printf("%d\n", ans);
	return 0;
}

