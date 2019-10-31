#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;
int p;

template<int N>
struct SegTree{
    struct node{
        int sum, l, r, lazy;
        node():lazy(0){}
        int len(){return r - l + 1;}
    }tr[N<<2];

    #define ls (id<<1)
    #define rs ((id<<1)|1)
    #define mid ((tr[id].l + tr[id].r) >> 1)

    void maintain(int id){ tr[id].sum = (tr[ls].sum + tr[rs].sum) % p;}

    void build(int id, int l, int r, int *&a){
        tr[id].l = l, tr[id].r = r;
        if(l == r){tr[id].sum = a[l]; return ;}
        build(ls, l, mid, a);
        build(rs, mid + 1, r, a);
        maintain(id);
    }

    inline void pushdown(int id){ if(tr[id].lazy){
        tr[ls].lazy = (tr[ls].lazy + tr[id].lazy) % p; tr[rs].lazy =  (tr[rs].lazy + tr[id].lazy) % p;
        tr[id].sum = tr[id].sum + tr[id].lazy * (tr[id].len()); 
    }}
    
    int query(int id, int l, int r){
        pushdown(id);
        if(tr[id].l >= l && tr[id].r <= r) return tr[id].sum;
        return (l <= mid ? query(ls, l, r) : 0) + (r > mid ? query(rs, l, r) : 0);
    }

    void update(int id, int x, int l, int r){
        if(tr[id].l >= l && tr[id].r <= r) {tr[id].lazy += x; return ;}
        if(l <= mid) update(ls, x, l, r);
        if(r >= mid) update(rs, x, l, r);
    }
    #undef ls, rs, mid
};

template<int N>
struct Graph{
    //Edges on tree; edges is the edge's to
    int head[N], cntE, next[N<<2], edges[N<<2];

    struct Node{
        int son, fa, top, id, size, dep;
        Node():size(0){}
        Node(int dep, int fa):fa(fa),size(1),dep(dep){}
    }nodes[N];


    void addEdge(int from, int to){edges[++cntE] = to, next[cntE] = head[from]; head[from] = cntE;}


    void dfs1(int x, int f, int dep){
        nodes[x] = Node(dep, f);
        
    }
};

int main(){
    return 0;
}