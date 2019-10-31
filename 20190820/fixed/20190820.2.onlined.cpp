#include<cstdio>
#define ul unsigned long long
#define fo(i, x, y) for(int i = x; i <= y; i ++)
using namespace std;

ul T, a, b, n, ans, a2[65];

ul f(ul a, ul b, ul c, ul n) {
    ul s = (n + 1) * (b / c);
    if(n % 2 == 0) s += n / 2 * (n + 1) * (a / c); else s += (n + 1) / 2 * n * (a / c);
    a %= c; b %= c;
    ul m = (a * n + b) / c;
    if(m == 0) return s;
    return s + n * m - f(c, c - b - 1, a, m - 1);
}

int main() {
    a2[0] = 1; fo(i, 1, 62) a2[i] = a2[i - 1] * 2;
    for(scanf("%llu", &T); T; T --) {
        scanf("%llu %llu %llu", &a, &b, &n);
        ans = 0;
        //fo(k, 0, 60) if(b & a2[k]) ans --;
        fo(k, 0, 60) ans += f(a, b, a2[k], n) - f(a, b, a2[k + 1], n) * 2;
        printf("%llu\n", ans);
    }
}

