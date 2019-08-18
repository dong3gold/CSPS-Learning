#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
using namespace std;
char s[400300]; int fail[400300];
int readS () 
{
    char ch = 0; int tot = 0;
    while (!islower(ch))
    {
        ch = getchar();
    }
    while (islower(ch))
    {
        s[tot++] = ch;
        ch = getchar();
    }
    return tot;
}

void getFail(int n)
{
    fail[0] = fail[1] = 0;
    for(int i = 1; i < n; i++){
        int j = fail[i];
        while(j && s[j] != s[i]) j = fail[j];
        fail[i + 1] =  s[i] == s[j] ? j + 1 : 0;
    }
}
int sum[400300];
int main(){
    int n = readS();
    getFail(n);
    int t = 0; sum[t++] = n;
    for(int i = n; i && fail[i]; i = fail[i]){
        sum[t++] = fail[i];
    }
    for(t = t - 1; t >= 0; t--){
        printf("%d ", sum[t]);
    }
}
