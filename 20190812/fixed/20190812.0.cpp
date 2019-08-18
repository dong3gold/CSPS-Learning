#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>

using namespace std;
char readchar(){
	char ch = 0;
	while(!isprint(ch)||ch==32) ch = getchar();
	return ch;
}
int readint(){
	char ch = 0; int X = 0;
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)){X = (X<<3)+(X<<1)+(ch^48); ch = getchar();}
	return X;
}

int GCD(int x, int y){
    return x % y ? GCD(y, x % y) : y;
}
int T, n, k; char c; bool isB = 0; int sumC[2];
struct block
{
    int num;
    bool isB;
}C[200200];

int tot = 0;
int split[2], sum = 0;
int main(){
	freopen("silly.in", "r", stdin);
	freopen("silly.out", "w", stdout);
    T = readint();
    memset(C, 0, sizeof(C));
    while(T--){
        n = readint();
        isB = 0; tot = 0; split[0] = split[1] = sumC[0] = sumC[1] = 0;
        sum = 0;
        k = readint(); c = readchar();
        C[0].num = k; C[0].isB = isB = (c == 'B');
        sumC[c=='B'] += k;
        for(int i = 1; i < n; i++){
            k = readint(); c = readchar();
            if(isB ^ (c == 'B')){
            	C[++tot].num = k;
			}
			else C[tot].num += k;
            sumC[c=='B'] +=  k;
            C[tot].isB = isB = (c == 'B');
        }
        if(sumC[0] && sumC[1]){
        	int t = GCD(sumC[0], sumC[1]);
        	sumC[0] /= t; sumC[1] /= t;
            for(int i = 0; i <= tot; i++){
            	isB = C[i].isB;
                split[isB] += C[i].num;
                if(split[isB] % sumC[isB] == 0){
                	int r = split[isB] / sumC[isB];
                	int p = r * sumC[isB^1] - split[isB^1];
                	if(p >= 0 && C[i+1].num > p){
                		C[i+1].num -= p;
                		split[0] = split[1] = 0;
                		sum++;
					}
					else if(C[i+1].num == p){
						i++; split[0] = split[1] = 0;
						sum++;
					}
				}
            }
            printf("%d\n", sum);
        }
        else {
            printf("%d\n", sumC[0] ? sumC[0] : sumC[1]);
        }
    }
}
