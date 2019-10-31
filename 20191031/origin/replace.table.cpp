#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;
template<typename _TP>
struct deque{
	_TP q[500200];
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
int n;
char _ss[500010];
int cnt = 0;
deque<bool> q;
deque<bool> q2;
int ans = 0;

int main(){
	
	while(1){
		scanf("%s", _ss); n = strlen(_ss); ans = 0;
		q.clean(); q2.clean();
		for(int i = 0; i < n; i++){
        if(_ss[i] == 'a' && _ss[i+1] == 'b') q.push_back(1), q.push_back(1), q.push_back(0), i++, ans++;
        else q.push_back(_ss[i] == 'b');
    }
    while(!q.empty() || !q2.empty()){
        if(!q.empty()){
            while(!q.empty() && q.front()){
                q.pop_front();
            }
            while(!q.empty() && !q.back()){
                q.pop_back();
            }
            while(!q.empty()){
                if(!(q.front() ^ cnt)){
                    if(cnt) {
                        q2.push_back(1), q2.push_back(1), q2.push_back(0), cnt = 0, ans++;
                        if(ans == 1000000007) ans = 0;
                    }
                    else cnt++;
                }
                else {
                    if(cnt) q2.push_back(cnt = 0);
                    q2.push_back(1);
                }
                q.pop_front();
            }
            if(cnt) q2.push_back(0);
        }else if(!q2.empty()){
            while(!q2.empty() && q2.front()){
                q2.pop_front();
            }
            while(!q2.empty() && !q2.back()){
                q2.pop_back();
            }
            while(!q2.empty()){
                if(!(q2.front() ^ cnt)){
                    if(cnt) {
                        q.push_back(1), q.push_back(1), q.push_back(0), cnt = 0, ans++;
                        if(ans == 1000000007) ans = 0;
                    }
                    else cnt++;
                }
                else {
                    if(cnt) q.push_back(cnt = 0);
                    q.push_back(1);
                }
                q2.pop_front();
            }
            if(cnt) q.push_back(0);
        }
	}
	printf("%d\n", ans);
	}
	return 0;
}

