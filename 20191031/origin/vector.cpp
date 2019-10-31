#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>

using namespace std;

int x[10000], y[10000], cnt = 0;
int lastans = 0;
int opt;
int a, b, l, r;

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &opt);
        if(opt == 1){ cnt++;
            scanf("%d%d", x + cnt, y + cnt);
            x[cnt] ^= lastans, y[cnt] ^= lastans;
        }
        else {
            scanf("%d%d%d%d", &a, &b, &l ,&r);
            a^= lastans, b^= lastans, l ^= lastans, r^=lastans; lastans = 0;
            for(int i = l; i <= r; i++){
                lastans = max(lastans, a * x[i] + b * y[i]);
            }
            printf("%d\n", lastans);
        }
    }
    return 0;
}