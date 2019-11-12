#include <iostream>
#include <cstring>
#include <algorithm>
#define maxn 100010
using namespace std;

namespace segmentTree{
	int n;
	int a[maxn];
	struct segmentTree
	{
		struct treeNode
		{
			int l, r;
			long long sum, lazy;

			treeNode(int l = 0, int r = 0, int sum = 0,int lazy = 0):l(l),r(r),sum(sum),lazy(lazy){}
			treeNode(const treeNode& rhs):l(rhs.l),r(rhs.r),sum(rhs.sum),lazy(rhs.lazy){}
			treeNode& operator = (const treeNode& rhs){l = rhs.l, r = rhs.r, sum = rhs.sum, lazy = rhs.lazy; return *this;}

			bool isLeaf(){return l == r;}
			unsigned int len(){return r - l + 1;}
		
		} tr[maxn << 2];
		
		
		
		#define ls (id << 1)
		#define rs (id << 1 | 1)
		#define mid ((tr[id].l + tr[id].r) >> 1)

		void maintain(int id){tr[id].sum = tr[ls].sum + tr[rs].sum;}
		void lazy(int id){
			if(tr[id].lazy){
				tr[ls].lazy += tr[id].lazy; tr[rs].lazy += tr[id].lazy;
				tr[ls].sum += tr[ls].len() * tr[id].lazy; tr[rs].sum += tr[rs].len() * tr[id].lazy;
				tr[id].lazy = 0;
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
				tr[id].lazy += x;
				tr[id].sum += x * tr[id].len();
				return ;
			}
			lazy(id);
			if(l <= mid) add(ls, x, l, r);
			if(r > mid) add(rs, x, l, r);
			maintain(id);
		}

		long long query(int id, int l, int r){
			if(tr[id].l >= l && tr[id].r <= r){
				return tr[id].sum;
			}
			lazy(id);
			return (l <= mid ? query(ls, l, r) : 0) + (r > mid ? query(rs, l, r) : 0);
		}
		#undef ls
		#undef rs
		#undef mid
	};
	segmentTree tr;
}


int m;
int main(){
	cin >> segmentTree::n >> ::m;
	for(int i = 1; i <= segmentTree::n; i++){
		cin >> i[segmentTree::a];
	}
	segmentTree::tr.build();
	for(int i = 0, opt, l, r, x; i < m; i++){
		cin >> opt;
		if(opt == 1){
			cin >> l >> r >> x;
			segmentTree::tr.add(1, x, l, r);
		}
		else{
			cin >> l >> r;
			cout << segmentTree::tr.query(1, l, r) << endl;
		}
	}
	return 0;
}