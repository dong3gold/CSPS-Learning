#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

namespace string{
	struct trie
	{
		struct Node
		{
			char val; int pre, last, cnt;
			Node *son, *bro;
			Node(char x = 0, int i = 0):val(0),pre(i),last(i),cnt(0),son(NULL),bro(NULL){} 	
		} *root, *rev;

		void insert(char *s, int id){
			Node *o = root; Node *k;
			while(*s){
				if(o->son == NULL){
					o->son = new Node(*s, id);
					o = o->son;
				}
				else {
					k = o->son;
					while(k && k->val != *s) k = k->bro;
					if(k == NULL) k = new Node(*s, id);
					o = k; o->last = id;
				}
				s++;
			}
		}

		void insert_rev(char *s, int id){
			Node *o = rev; Node *k;
			while(*s){
				if(o->son == NULL){
					o->son = new Node(*s, id);
					o = o->son;
					o->cnt++;
				}
				else {
					k = o->son;
					while(k && k->val != *s) k = k->bro;
					if(k == NULL) k = new Node(*s, id);
					o = k; o->last = id;
					o->cnt++;
				}
				s--;
			}
		}

		bool query(char *s, int& l, int &r){
			Node *o = root; Node *k;
			while(*s){
				k = o->son;
				while(k && k->val != *s) k = k->bro;
				if(k == NULL) return 0;
				o = k;
				s++;
			}
			l = o->pre, r = o->last; return 1;
		}

		int query_rev(char* s){
			Node *o = rev; Node *k;
			while(*s){
				k = o->son;
				while(k && k->val != *s) k = k->bro;
				if(k == NULL) return 0;
				o = k;
				s--;
			}
			return o->cnt;
		}
	};
	trie tr;
}

int n, q;

struct query{int x, s; query():s(-1){}}querys[100010];
char ss[50010][102];
char t[102];
void getquery(char *s, int i){
	if(string::tr.query(s, querys[i<<1].x, querys[i<<1|1].x)){
		querys[i<<1].s = querys[i<<1|1].s = i;
		
	}
	
}

void getans(int i){

}

int main(){
	getchar();
	return 0;
}