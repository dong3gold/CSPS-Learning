#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <queue>
#define ms(x) memset(x, 0, sizeof(x))
using namespace std;
int read(){
	int X = 0, w = 0; char ch = 0;
	while(!isdigit(ch)){w |= ch == '-'; ch = getchar();}
	while(isdigit(ch)){X = (X<<3) + (X<<1) + (ch^48); ch = getchar();}
	return w ? -X : X;
}
template<typename _TP>
struct deque{
	_TP q[400200];
	int head, tail;
	deque():head(0),tail(0){}
	bool empty(){return head == tail;}
	void clean(){
		head = tail = 0;
	}
	void push_front(const _TP& x){
		q[head] = x; tail++;
	}
	void push_back(const _TP& x){
		q[tail++] = x;
	}
	void pop_front(){
		if(!empty()) head++;
	}
	void pop_back(){
		if(!empty()) tail--;
	}
	unsigned int size(){return tail - head;}
	_TP operator [](const _TP& x){return q[head+x];}
	_TP* begin(){return q + head;}
	_TP* end(){return q + tail - 1;}
	_TP front(){return q[head];}
	_TP back(){return q[tail-1];}
	_TP back(int x){return q[tail-x-1];}
};
int p[100200];
int n, a[100200], left[100200], right[100200]; 
int last[100200], mx[100200], l, r, dp[100200];
int main(){
	freopen("array.in", "r", stdin);
	freopen("array.out", "w", stdout);
    n = read(); ms(last);
    l = 0; r = n; 
    for(int i = 1; i <= n; i++){
        p[i] = read(); a[i] = read();
        l = max(last[p[i]], l);
        left[i] = l;
        last[p[i]] = i;
    }
  	ms(mx); memset(dp, 0x7f, sizeof(dp));
  	dp[0] = 0; dp[1] = a[1];
  	::deque<int> q;
  	q.push_back(1);
    for(int i = 2; i <= n; i++){
    	while(!q.empty() && q.front() < left[i]) q.pop_front();
		while(!q.empty() && a[i] >= a[q.back()]) q.pop_back();
		q.push_back(i);
    	for(unsigned int j = 1; j < q.size();j++){
            dp[i] = min(dp[i], dp[q[j-1]] + a[q[j]]);
        }
        dp[i] = min(dp[i], a[q[0]] + dp[left[i]]);
	}
	printf("%d\n", dp[n]);
    return 0;
}
