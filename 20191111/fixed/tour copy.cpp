#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

#define FILE_IO
#ifdef FILE_IO
	#define FILE tour
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x)  to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif

namespace io
{
	const int SIZE = 1 << 22 | 1;
	char iBuf[SIZE], *iS, *iT, c;
	char oBuf[SIZE], *oS = oBuf, *oT = oBuf + SIZE;
	#define gc() (iS == iT ? iT = iBuf + fread(iS = iBuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	template<class I> void gi(I &x)
	{
		for(c = gc(); c < '0' || c > '9'; c = gc());
		for(x = 0; c >= '0' && c <= '9'; c = gc())
			x = (x << 3) + (x << 1) + (c & 15);
	}
	inline void flush()
	{
		fwrite(oBuf, 1, oS - oBuf, stdout);
		oS = oBuf;
	}
	inline void putc(char x)
	{
		*oS++ = x;
		if(oS == oT) flush();
	}
	template<class I> void print(I x)
	{
		if(x < 0) putc('-'), x = -x;
		static char qu[55];
		char *tmp = qu;
		do *tmp++ = (x % 10) ^ '0'; while(x /= 10);
		while(tmp-- != qu) putc(*tmp);
	}
	struct flusher{ ~flusher() { flush(); } }_;
	#undef gc
}

int n, m, l;

struct Graph{
	int edges[10000010], head[5000010], nxt[10000010], cnt;
	int chain_id[5000010], length[500010], chain_cnt;
	int max_length, ans, max_depth, min_need;
	vector<int> dep[5000010];
	int bag[5000010];

	Graph():cnt(0),chain_cnt(0),max_length(0),max_depth(0),min_need(0){memset(head, 0, sizeof(head)); memset(chain_id, 0, sizeof(chain_id)); memset(bag, 0, sizeof(bag));}
	void addEdge(int from, int to){
		edges[++cnt] = to; nxt[cnt] = head[from]; head[from] = cnt;
	}

	stack<pair<pair<pair<int, int>, int>, int> > s;
	void dfs(){
		s.push(make_pair(make_pair(make_pair(1, 0), 0), 0));
		while(!s.empty()){
			u = s.top().first.first.first, fa = s.top().first.first.second;
			d = s.top().first.second;
			dep[d].push_back(u);
			max_depth = max(max_depth, d);
			if(edges[head[u]] == fa){
				chain_id[u] = ++chain_cnt;
				length[chain_cnt] = 1;
				bag[length[chain_id[u]]]++;
				s.pop(); s.top().second = 1;
				continue;
			}
			int len = 0;
			for(int i = head[u]; i; i = nxt[i]){
				if(edges[i] != fa){
					if(!chain_id[u]) {
						s.push(make_pair(make_pair(make_pair(edges[i], u), d + 1), 0));
						ret = s.top().second;
						len = ret + 1;
						chain_id[u] = chain_id[edges[i]];
					}
					else if(len < dfs(edges[i], u, d + 1) + 1)
					{
						len = length[chain_id[u] = chain_id[edges[i]]] + 1;
					}
				
				}
			}
			bag[length[chain_id[u]]]--;
			bag[len]++;
			max_length = max(max_length, len);
			return length[chain_id[u]] = len;
		}
	}

	void del(int d){
		for(unsigned int i = 0; i < dep[d].size(); i++){
			if(min_need == length[chain_id[dep[d][i]]]) 
			{
				if(bag[length[chain_id[dep[d][i]]]] == 1)
					min_need--, ans--;
			}
			else if(min_need < length[chain_id[dep[d][i]]]) ans--;
				
			bag[length[chain_id[dep[d][i]]]--]--;
			bag[length[chain_id[dep[d][i]]]]++;
		}
		while(max_length && bag[max_length] == 0) max_length--;
	}

	int query(int l){
		if(ans) return ans;
		ans = 0;
		for(int i = max_length; i > 0; i--){
			if(!bag[i]) continue;
			if(bag[i] >= l) {
				ans += l * i;
				min_need = i;
				break;
			} 
			ans += i * bag[i];
			l -= bag[i];
		}
		return ans;
	}
} G;

int query[2000010];
int r[2000010];
bool del[2000010];
int ans[2000010];
long long output = 0;

bool cmp(int a, int b){return query[a] > query[b];}

int main(){
#ifdef FILE_IO
	start;
#endif
	io::gi(n), io::gi(m), io::gi(l);
	for(int i = 2, f; i <= n; i++){
		io::gi(f);
		G.addEdge(i, f);
		G.addEdge(f, i);
	}
	G.dfs(1, 0, 0);
	for(int i = 0; i < m; i++){
		io::gi(query[i]); r[i] = i;
	}
	sort(r, r + m, cmp);
	for(int i = 0; i < m; i++){
		for(int j = G.max_depth; j > query[r[i]]; j--) 
			G.del(j);
		G.max_depth = min(G.max_depth, query[r[i]]);
		ans[r[i]] = G.query(l);
	}
	for(int i = m - 1; i >=0; i--){
		output = (output * 233 + ans[i]) % 2148473648;
	}
	io::print(output * 233 % 2148473648);
	io::putc('\n');
	return 0;
}
