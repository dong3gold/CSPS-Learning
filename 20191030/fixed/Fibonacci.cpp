#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

template<typename T, int N, int M>
struct Martix{
    T **p;
    void adjust(){ p = (T**) malloc(sizeof(T*)*N); for(int i = 0; i < M; i++) p[i] = (T*) malloc(sizeof(T)*M);}
    void clear(){for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) p[i][j] = (T)0;}
    Martix(){adjust(); clear();}
    
    T* operator [] (const int& x) {return p[x];}


    template<int K>
    Martix<T, N, K> operator * (Martix<T, M, K>& B){
        Martix<T, N, K> C;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < K; j++){
                for(int k = 0; k < M; k++){
                    C[i][j] += p[i][k] * B[k][j];
                }
            }
        }
        return C;
    }
};

template<typename T, int N>
void pow(Martix<T, N, N> &ans, Martix<T, N, N> a, int p){
    ans.clear();
    for(int i = 0; i < N; i++) ans[i][i] = 1;
    while(p){
        if(p&1) ans = ans * a;
        a = a * a;
        p >>= 1;
    }
}

Martix<long long, 2, 2> Fib;
Martix<long long, 2, 2> ans;


int main(){
	//freopen("fib.out", "w", stdout);
    Fib[0][0] = 0, Fib[0][1] = 1, Fib[1][0] = 1, Fib[1][1] = 1;
    long long a, x, b, y;
    while(~scanf("%lld%lld%lld", &a, &x, &b)){
        pow(ans, Fib, a - 1);
        if(x - ans[1][0] >= 0 && (((x - ans[1][0]) % ans[1][1]) == 0)){
            y = (x - ans[1][0]) / ans[1][1];
            pow(ans, Fib, b - 1);
            printf("%lld\n", ans[1][0] + ans[1][1] * y);
        }
        else printf("-1\n");
    }
    return 0; 
}
