#include <iostream>
#include <cstring>
#include <algorithm>
#define maxn 100010
using namespace std;

int m; long long p;

namespace segmentTree{
	int n;
	int a[maxn];
	struct segmentTree
	{
		
		struct treeNode
		{
			int l, r;
			long long sum, add, mul;

			treeNode(int l = 0, int r = 0, int sum = 0,int add = 0, int mul = 1):l(l),r(r),sum(sum),add(add),mul(mul){}
			treeNode(const treeNode& rhs):l(rhs.l),r(rhs.r),sum(rhs.sum),add(rhs.add),mul(rhs.mul){}
			treeNode& operator = (const treeNode& rhs){l = rhs.l, r = rhs.r, sum = rhs.sum, add = rhs.add, mul = rhs.mul; return *this;}

			bool isLeaf(){return l == r;}
			unsigned int len(){return r - l + 1;}
		
		} tr[maxn << 2];
		
		
		
		#define ls (id << 1)
		#define rs (id << 1 | 1)
		#define mid ((tr[id].l + tr[id].r) >> 1)

		void maintain(int id){tr[id].sum = (tr[ls].sum + tr[rs].sum) % p;}
		void lazy(int id){
			if(tr[id].add || tr[id].mul != 1){
				tr[ls].add = (tr[id].mul * tr[ls].add % p + tr[id].add) % p; tr[ls].mul = (tr[ls].mul * tr[id].mul) % p;
				tr[ls].sum = (tr[ls].sum * tr[id].mul % p + tr[id].add * tr[ls].len() % p) % p;
				tr[rs].add = (tr[id].mul * tr[rs].add % p + tr[id].add) % p; tr[rs].mul = (tr[rs].mul * tr[id].mul) % p;
				tr[rs].sum = (tr[rs].sum * tr[id].mul % p + tr[id].add * tr[rs].len() % p) % p;
				tr[id].add = 0; tr[id].mul = 1;
			}
		}

		void build(int id = 1, int l = 1, int r = n){
			tr[id] = treeNode(l, r);
			if(tr[id].isLeaf()) {tr[id].sum = a[l]; return ;}
			build(ls, l, mid); build(rs, mid+1, r);
			maintain(id);
		}

		void add(int id, int x, int l, int r){
			if(tr[id].l >= l && tr[id].r <= r){
				tr[id].add = (tr[id].add + x) % p;
				tr[id].sum = (tr[id].sum + (x * tr[id].len()) % p) % p;
				return ;
			}
			lazy(id);
			if(l <= mid) add(ls, x, l, r);
			if(r > mid) add(rs, x, l, r);
			maintain(id);
		}

		void mul(int id, int x, int l, int r){
			if(tr[id].l >= l && tr[id].r <= r){
				tr[id].add = tr[id].add * x % p; tr[id].mul = tr[id].mul * x % p;
				tr[id].sum = tr[id].sum * x % p;
				return ;
			}
			lazy(id);
			if(l <= mid) mul(ls, x, l, r);
			if(r > mid) mul(rs, x, l, r);
			maintain(id);
		}

		long long query(int id, int l, int r){
			if(tr[id].l >= l && tr[id].r <= r){
				return tr[id].sum;
			}
			lazy(id);
			return ((l <= mid ? query(ls, l, r) : 0) + (r > mid ? query(rs, l, r) : 0)) % p;
		}
		#undef ls
		#undef rs
		#undef mid
	};
	segmentTree tr;
}

int main(){
	cin >> segmentTree::n >> ::m >> ::p;
	for(int i = 1; i <= segmentTree::n; i++){
		cin >> i[segmentTree::a]; i[segmentTree::a] %= p;
	}
	segmentTree::tr.build();
	for(int i = 0, opt, l, r, x; i < m; i++){
		cin >> opt;
		if(opt == 1){
			cin >> l >> r >> x;
			segmentTree::tr.mul(1, x % p, l, r);
		}
		else if(opt == 2){
			cin >> l >> r >> x;
			segmentTree::tr.add(1, x % p, l, r);
		}
		else if(opt == 3){
			cin >> l >> r;
			cout << segmentTree::tr.query(1, l, r) << endl;
		}
	}
	return 0;
}