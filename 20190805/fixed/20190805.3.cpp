#include <cstdio>
#define ls (id<<1)
#define rs (id<<1|1)
#define mid ((tr[id].l+tr[id].r)>>1)
#define root 1
using namespace std;
struct seg{
	int l, r;
	int sum, lazy;
	seg():l(0),r(0),sum(0),lazy(0){}
	seg(int l, int r):l(l),r(r),sum(0),lazy(0){}
}tr[100020<<2];

void maintain(int id){
	tr[id].sum = tr[ls].sum + tr[rs].sum;
}
void lazy(int id, int k){
	tr[id].lazy += k;
	tr[id].sum += k*(tr[id].r - tr[id].l + 1);
}
void pushdown(int id){
	if(tr[id].lazy){
		lazy(ls, tr[id].lazy);
		lazy(rs, tr[id].lazy);
		tr[id].lazy = 0;
	}
}
void build(int id, int l, int r){
	tr[id] = seg(l, r);
	if(l == r) return ;
	build(ls, l, mid);
	build(rs, mid+1, r);
	maintain(id);
}
void update(int id, int l, int r){
	if(tr[id].l >= l && tr[id].r <= r) {
		tr[id].lazy++; tr[id].sum += (tr[id].r -tr[id].l + 1);
		return;
	}
	pushdown(id);
	if(mid >= l) update(ls, l, r);
	if(mid < r) update(rs, l, r);
	maintain(id);
}
int query(int id, int t){
	if(tr[id].l == tr[id].r) {
		int sum = tr[id].sum;
		tr[id].sum = 0;
		return sum;
	}
	pushdown(id);
	if(t <= mid) return query(ls, t);
	else return query(rs, t);
}
int main(){
	int n; 
	scanf("%d", &n);
	int l, r;
	build(root, 1, 100005);
	for(int i = 0; i < n; i++){
		scanf("%d%d", &l, &r);
		printf("%d\n", query(root, l) + query(root, r));
		update(root, l + 1, r - 1);
	}
	return 0;
}
