#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <cctype>
using namespace std;
int n, H;
vector<int> G[21];
vector<int> R[21];
void addEdge(int x, int y){
	G[x].push_back(y);
	R[y].push_back(x);
}
bool C[21]; long long int now;
bool D[21];
unordered_map<long long int, pair<int, long long> > um;
long long sum = 0;
int tot = 1;
int step;
long long DS;
long long st[100000];
char readChar(){
	char ch = 0;
	while(!isprint(ch)||ch==32) ch = getchar();
	return ch;
}
void readM(){
	scanf("%d%d", &n, &H);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(readChar() == 49){
				addEdge(j, i);
			}
		}
	}
	memset(C, 0, sizeof(C));
	now = 0;
	for(auto j = G[0].begin(); j != G[0].end(); j++){
		C[*j] = 1;
		sum++;
	}
	H--;
}

int main(){
	readM();
	if(H == 0){
		printf("%d\n", G[0].size());
		return 0;
	}
	if(G[0].size() == 0) {
		printf("0\n");
		return 0;
	}
	while(H--){
		DS = 0;
		for(int i = 0; i < n; i++){
			D[i] = 0;
			for(auto j = R[i].begin(); j != R[i].end(); j++){
				D[i] ^= C[*j];
				DS += C[*j] ? 1 : 2;
			}
		}
		sum += DS;
		st[tot] = now;
		if(um.find(now) == um.end()) um[now] = make_pair(tot++, DS);
		else{
			step = tot - um[now].first;
			break;
		}
		now = 0;
		for(int i = 0; i < n; i++){
			now |= 1 << (C[i] = D[i]);
		}
	}
	if(step){
		long long SS = 0;
		for(int i = tot - step; i < tot; i++){
			SS += um[st[i]].first;
		}
		int k = tot - step;
		for(; H % step != 0; H--){
			sum += um[st[k++]].first;
		}
		sum += H/step * SS;
		printf("%lld", sum);
	}
	printf("%lld", sum);
	return 0;
}
