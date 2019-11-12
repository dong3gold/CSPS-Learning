#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <queue>
//#define de(x) memset(x, 0, sizeof(x))
using namespace std;

const int N=1000002;
char t[100];
char P[1000002];
struct AC_automaton{
    int tr[N][26],cnt;
    int e[N];
    int fail[N];
    void insert(char* s){
        int p=0;
        while(*s){
            int k=*s - 97;
            if(!tr[p][k]) tr[p][k] = ++cnt;
            p = tr[p][k];
            s++;
        }
        e[p]++;
    }
    void build(){
        queue<int> q;
        memset(fail, 0, sizeof(fail));
        for(int i = 0; i < 26; ++i) if(tr[0][i]) q.push(tr[0][i]);
        while(!q.empty()){
            int k = q.front(); q.pop();
            for(int i = 0; i < 26;++i){
                if(tr[k][i]){
                    fail[tr[k][i]] = tr[fail[k]][i];
                    q.push(tr[k][i]);
                }
                else tr[k][i] = tr[fail[k]][i];
            }
        }
    }
    int query(char *t){
        int p = 0, res = 0;
        while(*t) {
            p = tr[p][*t - 97];
            for(int j = p; j && ~e[j]; j = fail[j]) res += e[j], e[j] = -1;
        	t++;
		}
        return res;
    }
    /*
	void clean(){
    	de(fail);
    	de(tr);
    	de(e);
    	cnt = 0;
	}
	*/
};
AC_automaton ac;

int main(){
	int m;
	scanf("%d", &m);
	for(int i = 0; i < m; ++i){
		scanf("%s", t);
		ac.insert(t);
	}
	ac.build();
	scanf("%s", P);
	printf("%d\n", ac.query(P));
	return 0;
}
