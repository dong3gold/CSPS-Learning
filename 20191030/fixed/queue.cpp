#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;

int n, limit;
int H[100020], G[100020], dp[100020];
long long sum[100020];
int l = 0, r = 0;
int ans, mid; 

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

deque<int> q;

bool check(int x){
	q.clean();
	int p = 1;
	for(int i = 1; i <= n; i++){
		while(sum[i] - sum[p-1] > x) p++;
		while(!q.empty() && q.front() < p) q.pop_front();
		while(!q.empty() && H[q.back()] <= H[i]) q.pop_back();
		q.push_back(i);
		//for(int j = 0; j < q.size(); j++) printf("%d ", q[j]); printf("\n");
		dp[i] = dp[p-1] + H[q.front()];
		for(int j = 0; j < q.size() - 1; j++) dp[i] = min(dp[i], dp[q[j]] + H[q[j+1]]);
		if(dp[i] > limit) return 0;
	}
	return 1;
}

int main(){
	scanf("%d%d", &n, &limit); sum[0] = 0, dp[0] = 0;
	for(int i = 1; i <= n; i++){
		scanf("%d%d", H + i, G + i);
		sum[i] = sum[i-1] + G[i];
		l = max(l, G[i]); r += G[i];
	}
	while(l <= r){
		mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}

