#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
struct Node{
	int val, sz;
	Node* ch[2];
	//Node* pre;
	Node(){val = 0; sz = 1;memset(ch, 0, sizeof(ch));}
	Node(int x){val = x; sz = 1;memset(ch, 0, sizeof(ch));}
	int kcmp(int k){
		return ch[0] ? k == ch[0]->sz + 1 ? -1 : k < ch[0]->sz + 1 ? 0 : 1 : k == 1 ? -1 : 1;
	}
	void maintain(){sz = (ch[0] ? ch[0]->sz : 0) + (ch[1] ? ch[1]->sz : 0) + 1;}
}; Node* root;

void rotate(Node*& o, int d){
	Node* k = o->ch[d^1]; 
	o->ch[d^1] = k->ch[d]; k->ch[d] = o; 
	o->maintain(); k->maintain();
	o = k; 
}
void splay(Node*& o, int k){
	if(!o) return ;
	int d = o->kcmp(k);
	if(d != -1){
		if(d) k -= (o->ch[0] ? o->ch[0]->sz : 0) + 1; 
		Node* p = o->ch[d];
		int d2 = p->kcmp(k);
		int k2 = (d2 == 0 ? k : k - (p->ch[0] ? p->ch[0]->sz : 0) - 1);
		if(d2!=-1){
			splay(p->ch[d2], k2);
			if(d2 == d) rotate(o, d^1);
			else rotate(o->ch[d], d);
		}
		rotate(o, d^1);
	}
}
void build(Node*& o, int l, int r){
	if(r < l ||r < 0 || l > n + 1) return;
	int mid = (l+r) >> 1;
	o = new Node(mid);
	build(o->ch[0], l, mid - 1);
	build(o->ch[1], mid + 1, r);
	o->maintain();
}
void split(Node*& o, Node*& left, Node*& right){
	right = o->ch[1]; if(o->ch[1]) o->ch[1] = NULL;
	left = o; left->maintain();
}
void merge(Node*& left, Node*& right){
	left->ch[1] = right; right = NULL;
	left->maintain();
}
void flip(int l, int r){
	splay(root, r + 1);
	splay(root->ch[0], l);
	Node *right;
	split(root->ch[0], root->ch[0], right);
	splay(right, 1);
	Node *r2, *head;
	split(right, head, r2);
	if(r2){
		splay(r2, r2->sz);
		merge(r2, head);
		merge(root->ch[0], r2);
	}
	else{
		merge(root->ch[0], head);
	}
}
void change(int x){
	int i = 1;
	for(; i <= n - x + 1; i+=x){
		flip(i, i+x);
	}
	if(i <= n) flip(i, n+1);
}
void print(Node* o){
	if(o->ch[0]) print(o->ch[0]);
	if(o->val != 0 && o->val != n+1) printf("%d ", o->val);
	if(o->ch[1]) print(o->ch[1]);
}
int main(){
	scanf("%d", &n);
	build(root, 0, n + 1);
	for(int i = 2; i <= n; i++){
		change(i);
	}
	print(root);
	return 0;
}
