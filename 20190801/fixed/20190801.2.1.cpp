#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <stack>

using namespace std;
int a[59];
int tot = 1;
priority_queue<pair<int, int>, vector<pair<int, int> >, less<pair<int, int> > > q;
stack<pair<int, int> > s;
struct Hex{
	int value;
	int edge[6];
	int head;
	Hex(){value = 0; head = 0;}
}hex[10010];
void addEdge(int a, int b, int pos){
	hex[a].edge[pos] = b;
	hex[b].edge[(pos+3)%6] = a;
	hex[b].head = (pos + 4) % 6; 
}
void work(int now){
	int start = hex[now].head, end = start + 6;
	for(int i = start; i < end; i++){
		if(hex[now].edge[i%6] == 0) addEdge(now, ++tot, i%6);
	}
	for(int i = start; i < end; i++){
		if(hex[hex[now].edge[i%6]].edge[(i+2)%6] == 0) addEdge(hex[now].edge[i%6], hex[now].edge[(i+1)%6], (i+2)%6);
	}
	if(now < 10009) work(now+1);
}
void color(){
	for(int i = 1; i < 6; i++) 
		q.push(make_pair(0, i));
	for(int i = 1; i < 10011; i++){
		for(int j = 0; j < 6; j++){
			if(q.top().second == hex[hex[i].edge[j]].value) {
				s.push(q.top()); q.pop();
			}
			else{
				auto tmp = q.top(); q.pop();
				hex[i].value = tmp.second;
				tmp.first++; q.push(tmp);
				while(!s.empty()) {
					q.push(s.top()); s.pop();
				}
			}
		}
	}
}
int main(){
	int T, n;
	work(1);
	color();
	//scanf("%d", &T);
	while(T--){
		//scanf("%d", &n);
		printf("%d", hex[n]);
	}
	return 0;
}
