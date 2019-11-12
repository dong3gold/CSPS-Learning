#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

struct Graph{
	struct Edge
	{
		int to, flow, cap;
		Edge(int to = 0, int flow = 1, int cap = 1):to(to),flow(flow),cap(){}
	}edges[20000];
	int head[20000], next[20000], cnt;

	Graph():cnt(0){memset(head, 0 ,sizeof(head)); memset(next, 0 ,sizeof(next));}

	void addEdge(int from, int to){
		edges[++cnt] = Edge(to); next[cnt] = head[from]; head[from] = cnt;
	}



};

int main(){

	return 0;
}