#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector> 
#include <iostream>
using namespace std;
int prime[56560];
int k[56560];
bool vis[800000];
/* 
struct BigInt{
	static const int Base = 100000000;
	static const int Width = 8;
	vector<int> s;
	
	BigInt(long long num = 0){*this = num;};
	BigInt operator = (long long num){
		s.clear(); 
		do{
			s.push_back(num % Base);
			num /= Base;
		}while(num > 0);
		return *this;
	}
	BigInt operator = (BigInt x){
		s = x.s;
		return *this;
	}
	BigInt operator * (const int &b) const{
		BigInt c; c.s.clear(); int g = 0;
		for(int i = 0; i < s.size(); i++){
			c.s.push_back(((long long) b * s[i] + g) % Base);
			g = ((long long) b*s[i] + g) / Base;
		}
		if(g) c.s.push_back(g);
		return c;
	}
	BigInt operator *= (const int &b){
		*this = *this*b; return *this;
	}
	friend ostream& operator << (ostream &out, const BigInt &x) {
		out << x.s.back();
		for(int i = x.s.size() - 2; i >= 0; i--){
			char buf[20];
			sprintf(buf, "%08d", x.s[i]);
			int len = strlen(buf);
			for(int j = 0; j < len; j++) out << buf[j];
		}
		return out;
	}
	void print(){
		printf("%d", s.back());
		for(int i = s.size() - 2; i >= 0; i--){
			printf("%08d", s[i]);
		}
		printf("\n");
	}
};

*/ 
int seive(int n){
	vis[1] = 1; int tot = 1;
	for(int i = 2; i < n; i++){
		if(!vis[i]){
			prime[tot] = i;
			for(int j = i; j < n; j+=i){
				vis[j] = 1; int num = 0; int p = j;
				while(p&&p%i==0) p/=i, num++;
				k[tot] += num;
			}
			tot++;
		}
	}
	return tot;
}

int main(){
	int n; memset(k, 0, sizeof(k));
	scanf("%d", &n);
	int tot = seive(n+1);
	BigInt sum = 1;
	for(int i = 1; i < tot; i++){
		sum *= k[i]*2 + 1;
	}
	sum.print();
	return 0;
}
