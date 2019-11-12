#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <deque>

using namespace std;

int s[1000020];
int ans = 0;
deque<bool> d;
deque<int> t;

int len = 0;
int n, m;

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++){
		scanf("%d", s + i);
	}
	for(int i = 0, opt, ch; i < m; i++){
		scanf("%d%d", &opt, &ch); len++;
		if(opt == 0){
			t.push_back(ch);
			for(int i = len - 1; i > 0; i--){
				if(s[i] == ch){
					d[i] = d[i-1];
				}
				else {
					if(d[i-1])  ans--;
					d[i] = d[i-1] = 0;
				}
			}
			if(ch == s[0]) ans++;
			d.push_back(ch == s[0]); t.push_front(ch);
		}
		else
		{
			int i = 0;
			for(; i < len - 1; i++){
				if(t[i] != s[i+1]) {
					d.push_front(0); break;
				}
			}
			if(i == len) d.push_front(1), ans++;
			t.push_front(ch);
		}
		printf("%d\n", ans);
	}
	return 0;
}