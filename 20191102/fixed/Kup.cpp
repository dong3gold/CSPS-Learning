#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;

template<typename T>
struct Stack
{
    T s[10000];
    int top;

    Stack():top(0){}

    bool empty(){return !top;}
    int size(){return top;}

    void push(int x) {(top++)[s] = x;}
    bool pop(int x) {if(!empty()) return --top, 1; else return 0;}
    T top(){return (top - 1)[s];}
    T* begin(){return s + max(top - 1, 0);}
    T* end(){return s;}

    T& operator [](const int &x) {return s[top - 1 - x];}

    void clear(){top = 0;}
};

::Stack<int> s;


int sum[2010][2010];
int k, n;


int main(){
    scanf("%d%d", &k, &n); int low = k, upp = k << 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(scanf("%d", sum[i] + j) && sum[i][j] > upp) sum[i][j] = -1;
            else if(sum[i][j] >= low && sum[i][j] <= upp) {printf("%d %d %d %d", i, j, i, j); return 0;}
        }
    }
    for(int i = 1; i < n; i++) if((~sum[0][i] && ~sum[0][i-1])) sum[0][i] += sum[0][i-1];
    for(int i = 1; i < n; i++) if((~sum[i][0] && ~sum[i-1][0])) sum[i][0] += sum[i-1][0];
    for(int i = 2; i < n; i++){
        for(int j = 2; j < n; j++){
            if(~sum[i][j]){
                if(~sum[i][j])
            }
        }
    }
    return 0;
}