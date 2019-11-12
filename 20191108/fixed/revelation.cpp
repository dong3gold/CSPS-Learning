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

int n, mn, mx; 
int to[1000010], in1[1000010], in2[1000010];
int q1[1000010], q2[1000010]; bool flag1[1000010], flag2[1000010];
int cnt1 = 0, cnt2 = 0;


int get_length(int u, bool *flag){
	flag[u] = 1; int sum = 1, v = u;
	while(!flag[to[v]]){
		flag[to[v]] = 1;
		sum++;
		v = to[v];
	}
	return sum == 1 ? 2 : sum;
}

int main(){
	scanf("%d", &n);
	for(int i = 1, v; i <= n; i++){
		scanf("%d", &v);
		to[i] = v; in1[v]++, in2[v]++;
	}

	for(int i = 1; i <= n; i++){
		if(!in1[i]) (q1[cnt1++] = i)[flag1] = 1;
		if(!in2[i]) (q2[cnt2++] = i)[flag2] = 1;
	}
	int num = 0;
	while(num < cnt1){
		int k = q1[num], u = to[k];
		if(!flag1[u]){
			mn++; flag1[u] = 1;
			int v = to[u]; in1[v]--;
			if(!in1[v]){
				(q1[cnt1++] = v)[flag1] = 1;
			}
		}
		num++;
	}
	for(int i = 1; i <= n; i++){
		if(!flag1[i]){
			mn += (get_length(i, flag1) + 1) / 2;
		}
	}

	num = 0;

	while(num < cnt2){
		int k = q2[num], u = to[k];
		if(!flag2[u]){
			mx++; (q2[cnt2++] = u)[flag2] = 1;
		}
		num++;
	}
	for(int i = 1; i <= n; i++){
		if(!flag2[i]){
			mx += get_length(i, flag2) - 1;
		}
	}
	printf("%d %d\n", mn, mx);
	return 0;
}
