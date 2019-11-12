
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
const int MAXV = 100005;
const int MAXP = 2e7 + 5;
template <typename T> void chkmax(T &x, T y) {x = max(x, y); }
template <typename T> void chkmin(T &x, T y) {x = min(x, y); } 
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
template <typename T> void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T> void writeln(T x) {
	write(x);
	puts("");
}
struct MainSegmentTree {
	int n, val[MAXN], del[MAXN];
	void init(int x) {
		n = x;
		memset(val, 0, sizeof(val));
		memset(del, 0, sizeof(del));
	}
	void modify(int l, int r, int d) {
		if (r >= n) r = n;
		if (l <= r) {
			del[l] += d;
			del[r + 1] -= d;
		}
	}
	void getans(int &Max, long long &sum) {
		for (int i = 1; i <= n; i++) {
			del[i] += del[i - 1];
			val[i] += del[i];
		}
		for (int i = 1; i <= n; i++) {
			del[i] = 0;
			chkmax(Max, val[i]);
			sum += val[i];
		}
	}
} MST;
struct AssitantSegmentTree {
	struct Node {
		int lc, rc;
		short sum;
	} a[MAXP];
	vector <int> b[MAXV];
	int k, root[MAXV], size, tmp;
	void init(int y, int x) {
		k = x;
		for (int i = 1; i < MAXV; i++)
			b[i].push_back(0);
	}
	int add(int &root, int l, int r, int pos) {
		if (root == 0) root = ++size;
		if (l == r) return ++a[root].sum;
		int mid = (l + r) / 2;
		a[root].sum++;
		if (mid >= pos) return add(a[root].lc, l, mid, pos);
		else return add(a[root].rc, mid + 1, r, pos);
	}
	int dec(int &root, int l, int r, int pos) {
		if (root == 0) root = ++size;
		if (l == r) return a[root].sum--;
		int mid = (l + r) / 2;
		a[root].sum--;
		if (mid >= pos) return dec(a[root].lc, l, mid, pos);
		else return dec(a[root].rc, mid + 1, r, pos);
	}
	int suf(int root, int l, int r, int ql, int qr) {
		if (a[root].sum == 0 || ql > qr) return 0;
		if (l == r) return l;
		int mid = (l + r) / 2;
		if (mid >= qr) return suf(a[root].lc, l, mid, ql, qr);
		if (mid + 1 <= ql) return suf(a[root].rc, mid + 1, r, ql, qr);
		int tmp = suf(a[root].rc, mid + 1, r, mid + 1, qr);
		if (tmp) return tmp;
		else return suf(a[root].lc, l, mid, ql, mid);
	}
	int pre(int root, int l, int r, int ql, int qr) {
		if (a[root].sum == 0 || ql > qr) return 0;
		if (l == r) return l;
		int mid = (l + r) / 2;
		if (mid >= qr) return pre(a[root].lc, l, mid, ql, qr);
		if (mid + 1 <= ql) return pre(a[root].rc, mid + 1, r, ql, qr);
		int tmp = pre(a[root].lc, l, mid, ql, mid);
		if (tmp) return tmp;
		else return pre(a[root].rc, mid + 1, r, mid + 1, qr);
	}
	void ins(int val, int pos) {
		if (add(root[val], 1, b[val].size() - 1, pos) >= 2) return;
		int l = max(1, b[val][pos] - k + 1), r = b[val][pos];
		if (tmp = suf(root[val], 1, b[val].size() - 1, 1, pos - 1)) chkmax(l, b[val][tmp] + 1);
		if (tmp = pre(root[val], 1, b[val].size() - 1, pos + 1, b[val].size() - 1)) chkmin(r, max(0, b[val][tmp] - k));
		MST.modify(l, r, 1);
	}
	void del(int val, int pos) {
		if (dec(root[val], 1, b[val].size() - 1, pos) >= 2) return;
		int l = max(1, b[val][pos] - k + 1), r = b[val][pos];
		if (tmp = suf(root[val], 1, b[val].size() - 1, 1, pos - 1)) chkmax(l, b[val][tmp] + 1);
		if (tmp = pre(root[val], 1, b[val].size() - 1, pos + 1, b[val].size() - 1)) chkmin(r, max(0, b[val][tmp] - k));
		MST.modify(l, r, -1);
	}
} AMS;
int n, m, k, mp[MAXN][MAXN], pos[MAXN][MAXN];
int main() {
	read(n), read(m), read(k);
	MST.init(m - k + 1);
	for (register int i = 1; i <= n; i++)
	for (register int j = 1; j <= m; j++)
		read(mp[i][j]);
	register int Max = 0; register long long sum = 0;
	AMS.init(m, k);
	for (register int j = 1; j <= m; j++)
	for (register int i = 1; i <= n; i++) {
		int tmp = mp[i][j];
		if (AMS.b[tmp][AMS.b[tmp].size() - 1] != j) AMS.b[tmp].push_back(j);
		pos[i][j] = AMS.b[tmp].size() - 1;
	}
	for (register int i = 1; i <= k - 1; i++)
	for (register int j = 1; j <= m; j++)
		AMS.ins(mp[i][j], pos[i][j]);
	for (register int i = k; i <= n; i++) {
		for (register int j = 1; j <= m; j++)
			AMS.ins(mp[i][j], pos[i][j]);
		MST.getans(Max, sum);
		for (register int j = 1; j <= m; j++)
			AMS.del(mp[i - k + 1][j], pos[i - k + 1][j]);
	}
	printf("%d %lld\n", Max, sum);
	return 0;
}