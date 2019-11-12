#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <queue>

using namespace std;

int A[100010], B[100010];
int r[100010], code[100010], tail, head;
int rc[100010], out[100010];
int n;

queue<int> q;


bool cmp(int a, int b){return A[a] < A[b];}
bool cmp2(int a, int b){return a > b ? B[code[b]] > A[r[a]] : B[code[a]] < A[r[b]];}

int main(){
    //freopen("game.in", "r", stdin); freopen("game.out", "w", stdout);
	scanf("%d", &n); tail = n - 1;
	for(int i = 0; i < n; i++) scanf("%d", A + i), i[r] = i;
	for(int i = 0; i < n; i++) scanf("%d", B + i);
	sort(r, r + n, cmp);
	sort(B, B + n);
	for(int i = 0, j = 0; i < n; i++){
		if(B[i] > A[r[j]]) q.push(i), j++;
		else {
			q.push(i),code[tail--] = q.front(), q.pop();
		}
	}
	while(!q.empty()) code[head++] = q.front(), q.pop();
	for(int i = 0; i < head; i++) rc[i] = i;
	sort(rc, rc + head, cmp2);
	for(int i = 0; i < head; i++){
		out[r[i]] = B[code[rc[i]]];
	}
	for(int i = head; i < n; i++){
		out[r[i]] = B[code[i]];
	}
	for(int i = 0; i < n; i++){
		printf("%d ", out[i]);
	}
	return 0;
}
