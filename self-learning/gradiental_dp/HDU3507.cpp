#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;
int read(){
	int X = 0, w = 0; char ch = 0;
	while(!isdigit(ch)){w |= ch == '-'; ch = getchar();}
	while(isdigit(ch)){X = (X<<3) + (X<<1) + (ch^48); ch = getchar();}
	return w ? -X : X;
}
template<typename _TP>
struct deque{
	_TP q[100020];
	int head, tail;
	deque():head(0),tail(0){}
	bool empty(){return head == tail ;}
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
	int size(){return tail - head;}
	_TP operator [](const _TP& x){return q[head+x];}
	_TP* begin(){return q + head;}
	_TP* back(){return q + tail - 1;}
	_TP get_begin(int x){return q[head + x];}
	_TP get_back(int x){return q[tail-x-1];}
};
int n, m;
int a[100020];
int dp[100020];
::deque<int> q;
int getUp(int x, int y){
	return (a[x]+a[y])*(a[x]-a[y]) + dp[x] - dp[y];
}
int getDown(int x, int y){
	return 2*(a[x] - a[y]);
}
void getDp(int i, int x){
	dp[i] = dp[x] + (a[i]-a[x])*(a[i]-a[x]) + m;
}

int main(){
	while(scanf("%d%d", &n, &m) == 2){
		a[1] = read();
		for(int i = 2; i <= n; i++){
			a[i] = a[i - 1] + read();
		}
		a[0] = 0; dp[0] = 0;
		q.clean(); q.push_front(0);
		for(int i = 1; i <= n; i++){
			while(q.size() > 1 && getUp(q[1], q[0]) <= a[i]*getDown(q[1], q[0])) 
				q.pop_front();
			getDp(i, q[0]);
			while(q.size() > 1 && getUp(i, q.get_back(0))*getDown(q.get_back(0), q.get_back(1)) <= getUp(q.get_back(0), q.get_back(1)) * getDown(i, q.get_back(0))) 
				q.pop_back();
			q.push_back(i);
		}
		printf("%d\n",dp[n]);
	}
}
