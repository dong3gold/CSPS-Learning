#include <cstdio>
#include <cctype>
int a[100020], b[100020], c[100020];
int f1[100020], f2[100020];

int read(){
	int X = 0, w = 0; char ch =0;
	while(!isdigit(ch)){w=ch=='-';ch=getchar();}
	while(isdigit(ch)){
		X = (X<<3) + (X<<1) + (ch^48);
		ch = getchar();
	}
	return w ? -X : X;
}
int main(){
	int n = read(), ans = 0;bool fin = 0;
	for(int i = 0; i < n; i++){
		a[i] = read();
	}
	for(int i = 0; i < n; i++){
		f1[b[i] = read()]++;
	}
	for(int i = 0; i < n; i++){
		f2[c[i] = read()]++;
	}
	while(!fin){
		fin = 1;
		for(int i = 0; i < n; i++){
			if(a[i] && (!f1[a[i]] || !f2[a[i]])){
				fin = 0;
				a[i] = 0;
				f1[b[i]]--, f2[c[i]]--;
				ans++;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
