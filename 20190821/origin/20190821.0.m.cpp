#include <cstdio>
#define lowbit(x) (x&-x)
using namespace std;
int count(int x){
    int k = 0;
    while(x){x -= lowbit(x); k++;}
    return k;
}
int choice[20][184760]; int tot[20];
int main(){
	freopen("ratio.txt", "w", stdout);
    int n = 1 << 15;
    for(int i = 0; i < 20; i++) tot[i] = 0;
    for(int i = 0; i < n; i++){
        int t = count(i);
        choice[t][tot[t]++] = i;
    }
    for(int i = 0; i < 20; i++){
        printf("{");
        for(int j = 0; choice[i][j]; j++){
            printf("%d,", choice[i][j]);
        }
        printf("},");
    }
    return 0;
}
