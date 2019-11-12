#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;

template <typename _Tp>
void read(_Tp &x){
	x = 0; char ch(0);
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)){ x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
}
long long n;
int m, q, op;
long long out = 0;
long long output[400020], ans = 0;
struct home
{
	long long cnt, size, k, r;
	long long cap, ful;
	home() {}
	home(int cnt, int size) : cnt(cnt), size(size), k(0), r(0), cap(size * cnt), ful(cap) {}
	long long operator() () {
		if (~size)
			return (long long)k * size * size + r * r;
		else
			return out;
	}
	long long add(long long num){
		if (num <= cap){cap -= num; k = (ful - cap) / size; r = (ful - cap) % size; return 0;} 
		else{k = cnt; r = 0; long long _cap = cap; cap = 0; return num - _cap;}
	}
	long long cut(long long num){
		if (num <= ful - cap){cap += num; k = (ful - cap) / size; r = (ful - cap) % size; return 0;}
		else{k = 0; r = 0; long long _cap = cap; cap = ful; return num - ful + cap;}
	}

	bool operator>(const home &b) { return (size == b.size && cnt > b.cnt) || size > b.size; }
} homes[400020];

int nxt[400020], pre[400020];
int tail, head;
int que[400020], start[400020];
bool cmp(int a, int b) { return homes[a] > homes[b]; }

void init(int m, int t){
	stable_sort(start, start + m, cmp);
	long long cap = n;
	if (m > 0){
		cap = homes[start[0]].add(cap);
		ans += homes[start[0]]();
	}
	int i = 1;
	while (cap && i < m){
		cap = homes[start[i]].add(cap);
		ans += homes[start[i]]();
		i++;
	}
	pre[start[0]] = -1; nxt[start[0]] = start[1];
	for (int j = 1; j < m; j++)nxt[start[j]] = start[j + 1], pre[start[j]] = start[j - 1];
	nxt[start[m - 1]] = -1;
	if (i >= m) out = cap, tail = -1, ans += out;
	else tail = homes[start[i - 1]].cap == 0 ? start[i] : start[i-1];
	output[t] = ans;
}

void del(int x, int i)
{
	if (x == tail) tail = nxt[tail];
	if (pre[x] != m + q && pre[x] != -1) nxt[pre[x]] = nxt[x];
	if (nxt[x] != -1 && nxt[x] != m + q) pre[nxt[x]] = pre[x];
	if (tail == m + q) tail = -1;
	while (homes[x].cap != homes[x].ful){
		if (tail == -1 || tail == m + q){
			ans -= homes[x]();
			ans += homes[x].ful - homes[x].cap;
			out += homes[x].cap;
			homes[x].cut(homes[x].ful - homes[x].cap);
		}
		else{
			ans -= homes[x](); ans -= homes[tail]();
			long long cut = homes[tail].add(homes[x].ful - homes[x].cap);
			homes[x].cut(homes[x].ful - homes[x].cap - cut);
			ans += homes[x](); ans += homes[tail]();
			if (homes[tail].cap == 0) tail = nxt[tail];
		}
	}
	output[i] = ans;
}

int main()
{
	freopen("forest.in", "r", stdin); freopen("forest2.out", "w", stdout);
	read(n);read(m);read(q);read(op);
	for (int i = 0, x, y; i < m; i++){
		read(x);read(y);
		homes[i] = home(x, y);
		start[i] = i;
	}
	if (op){
		for (int i = m, x, y; i < m + q; i++){
			read(x);read(y);
			homes[i] = home(x, y);
			start[i] = i;
		}
		init(m+q, q);
	}
	else{
		for (int i = 0; i < q; i++) read(que[i]);
		init(m, q);
	}
	//for(int i = 0; i < m + q; i++) printf("%d\n", homes[rnk[i]].size);
	if (op) for (int i = q - 1; i >= 0; i--) del(m + i, i);
	else for (int i = 0; i < q; i++) del(que[i] - 1, i);
	if(!op) printf("%lld\n", output[q]);
	for(int i = 0; i < q; i++) printf("%lld\n", output[i]);
	if(op) printf("%lld\n", output[q]);
	return 0;
}
