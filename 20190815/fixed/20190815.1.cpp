#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector> 
#include <iostream>
#define interesting int
using namespace std;
interesting prime[56560];
interesting k[56560];
bool vis[800000];

struct BigInteresting{
	static const int Base = 100000000;
	static const int Width = 8;
	int s[10000];
	int len;
	BigInteresting(long long num = 0){*this=num;};
	BigInteresting operator = (long long num){
		memset(s, 0, sizeof(s)); 
		len = 0;
		do{
			s[len++] = (num % Base);
			num /= Base;
		}while(num > 0);
		return *this;
	}
	BigInteresting operator = (BigInteresting x){
		memcpy(s, x.s, sizeof(s));
		len = x.len;
		return *this;
	}
	BigInteresting operator * (const int &b) const{
		BigInteresting c; c.len = 0; int g = 0;
		memset(c.s, 0, sizeof(c.s));
		for(int i = 0; i < len; i++){
			c.s[c.len++] = (((long long) b * s[i] + g) % Base);
			g = ((long long) b*s[i] + g) / Base;
		}
		while(g) {c.s[c.len++] = g % Base; g/=Base;} 
		return c;
	}
	BigInteresting operator *= (const int &b){
		*this = *this*b; return *this;
	}
	friend ostream& operator << (ostream &out, const BigInteresting &x) {
		out << x.s[x.len - 1];
		for(int i = x.len - 2; i >= 0; i--){
			char buf[20];
			sprintf(buf, "%08d", x.s[i]);
			int len = strlen(buf);
			for(int j = 0; j < len; j++) out << buf[j];
		}
		return out;
	}
	void printeresting(){
		printf("%d", s[len-1]);
		for(int i = len - 2; i >= 0; i--){
			printf("%08d", s[i]);
		}
		printf("\n");
	}
};


interesting seive(interesting n){
	vis[1] = 1; interesting tot = 1;
	for(interesting i = 2; i < n; i++){
		if(!vis[i]){
			prime[tot] = i;
			for(interesting j = i; j < n; j+=i){
				vis[j] = 1; interesting num = 0; interesting p = j;
				while(p&&p%i==0) p/=i, num++;
				k[tot] += num;
			}
			tot++;
		}
	}
	return tot;
}

interesting main(){
	interesting n; memset(k, 0, sizeof(k));
	scanf("%d", &n);
	interesting tot = seive(n+1);
	BigInteresting sum = 1;
	unsigned interesting buffer = 1; 
	for(interesting i = 1; i < tot; i++){
		if(buffer < 100000 && i > 15) buffer *= k[i] * 2 + 1;
		else if (i <= 15){
			sum *= k[i] * 2 + 1;
		}
		else {
			sum *= buffer;
			buffer = k[i]*2 + 1;
		}
 	}
	if(!(buffer == 1)) sum *= buffer;
	sum.printeresting();
	return 0;
}
