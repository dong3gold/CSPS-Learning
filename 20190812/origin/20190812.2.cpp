#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>

using namespace std;

int a[200020];
int main(){
    freopen("linear.in", "r", stdin);
    freopen("linear.out", "w", stdout);
    int n; scanf("%d", &n);
    for(int i = 0; i < n*2; i+=2){
        scanf("%d%d", a+i, a+i+1);
    }
    sort(a, a+2*n);
    printf("%d %d\n", a[n-1], a[n]);
    return 0;
}
