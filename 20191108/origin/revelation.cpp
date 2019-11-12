#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <map>

//#define FILE_IO
#ifdef FILE_IO
	#define FILE revelation
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif

using namespace std;

int in1[1000020], in2[1000020];
int to1[1000020], to2[1000020];
int from[1000020], head[1000020], nxt[1000020], cnt = 0;

int n;
int ans1 = 0, ans2 = 0;

int main(){
	scanf("%d", &n);
	for(int i = 0, v; i < n; i++){
		scanf("%d", &v); in1[v - 1]++; in2[v - 1]++; to1[i] = v - 1, to2[i] = v - 1;
		from[++cnt] = i; nxt[cnt] = head[v - 1]; head[v - 1] = cnt;
	}
	for(int i = 0, mx = 0, mxn; i < n; ++i, mx = 0){
		for(int j = 0; j < n; j++){
			if(in1[j] > mx) mx = in1[j], mxn = j;
			else if(in1[j] == mx && to1[j]) mxn = j;
		}
		if(mx == 0) break; 
		in1[mxn] = 0;
		in1[to1[mxn]]--;
		to1[mxn] = 0;
		for(int j = head[mxn]; j; j = nxt[j]) to1[from[j]] = 0;
		++ans1;
	}
	for(int i = 0, mn = 0x3f3f3f3f, mnn; i < n; ++i, mn = 0x3f3f3f3f){
		for(int j = 0; j < n; j++){
			if(in2[j] < mn && in2[j] > 0) mn = in2[j], mnn = j;
			else if(in2[j] == mn && !to2[j]) mnn = j;
		}
		if(mn == 0x3f3f3f3f) break;
		in2[mnn] = 0;
		in2[to2[mnn]]--;
		to2[mnn] = 0;
		for(int j = head[mnn]; j; j = nxt[j]) to2[from[j]] = 0;
		++ans2;
	}
	printf("%d %d\n", ans1, ans2);
	return 0;
}
