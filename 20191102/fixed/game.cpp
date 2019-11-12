#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <queue>

using namespace std;

struct num{
	int s, id;
	num(){}
	num(int s, int id):s(s),id(id){}
	bool operator<(const num& b) const {return s == b.s ? id < b.id : s < b.s;}
} A[100010], B[100010];


int r[100010], code[100010], tail, head;
int out[100010];
int n;

queue<int> q;

inline bool get(int a){return B[code[a]].s > A[a].s;}

inline bool cmp(int a, int b){
	if(A[a].id < A[b].id){
		if(a < b) {return B[code[a]].s <= A[b].s;}
		else {return 0;}
	}
	else {
		if(a < b){return 1;}
		else {return B[code[b]].s > A[a].s;}
	}
}
inline bool cmp2(int a, int b){
	return A[a].id < A[b].id ? (B[code[a]].s <= B[code[b]].s) : (B[code[a]].s > B[code[b]].s);
}

inline bool cmp3(int a, int b){
	bool d1 = get(a), d2 = get(b);
	if(d1 && d2) return cmp(a, b);
	if(!(d2 || d1)) return cmp2(a, b);
	if(d1){
		if(A[a].id < A[b].id) {
			return B[a].s > B[b].s || !((B[a].s < A[b].s) ^ (A[a].s > B[b].s));
		}
		else{
			return !(B[a].s > B[b].s || !((B[a].s < A[b].s) ^ (A[a].s > B[b].s)));
		}
	}
	else{
		if(A[a].id < A[b].id) {
			return !(B[a].s > B[b].s || !((B[a].s < A[b].s) ^ (A[a].s > B[b].s)));
		}
		return B[a].s > B[b].s || !((B[a].s < A[b].s) ^ (A[a].s > B[b].s));
	}
}


int main(){
	freopen("game.in", "r", stdin); freopen("game.out", "w", stdout);
	scanf("%d", &n); tail = n - 1; head = 0;
	for(int i = 0, a; i < n; i++) {
		scanf("%d", &a); 
		A[i] = num(a, i);
	}
	for(int i = 0, b; i < n; i++) {
		scanf("%d", &b);
		B[i] = num(b, i);
	}
	sort(A, A + n); sort(B, B + n);
	for(int i = 0, j = 0; i < n; i++){
		if(A[j].s < B[i].s){
			q.push(i); j++;
		}
		else{
			q.push(i); 
			code[tail--] = q.front(); 
			q.pop();
		}
	}
	while(!q.empty()) {
		code[head++] = q.front();
		q.pop();
	}
	for(int i = 0; i < n; i++) r[i] = i;
	sort(r, r + n, cmp3); 
	for(int i = 0; i < n; i++) 
		out[A[r[i]].id] = B[code[i]].s;
	for(int i = 0; i < n; i++) printf("%d ", out[i]);
	return 0;
}
