#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#define lowbit(i) (i&-i);
using namespace std;
int get1 (long long i)
{
    int t = 0;
    while (i) {
        i -= lowbit(i);
        t++;
    }
    return t;
}
int A[35], B[35], C[35];
int main ()
{
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", A + i);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", B+i);
        B[i] = A[i] - B[i];
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", C + i);
        C[i] = A[i] - C[i];
    }
    long long per = 1 << n; long long tot = 0;
    for (long long i = 1 << (k-1); i < per; i++) 
    {
    	if(get1(i) < k) continue;
        long long j = i, sum0 = 0, sum1 = 0, num = 0;
        for(; j; j >>= 1, num++){
            if(j&1){
                sum0 += B[num];
                sum1 += C[num];
            }
        }
        if(sum0 > 0 && sum1 > 0) tot++;
    }
    printf("%lld\n", tot);
    return 0;
}
