#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <functional>

#define FILE_IO
#ifdef FILE_IO
	#define FILE bag
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif

using namespace std;
int n, m, T;
struct thing{
	int weight, value;
	thing(int weight = 0, int value = 0):weight(weight),value(value){}
	bool operator< (const thing& b) const{return weight == b.weight ? value > b.value : weight > b.weight;}
}things[100002];

struct thingCmp{bool operator() (const thing& lhs, const thing& rhs) const {return lhs.value > rhs.value;}};

int bags[100002], ans;

struct fwk{
	int c[100002], big;
	void clear(){
		big = 0; memset(c, 0, sizeof(c));
	}
	fwk(){clear();}
	
	#define lowbit(x) (x&-x)
	void update(int x, int v){
		for(; x <= big; x += lowbit(x)){
			c[x] = max(c[x], v);
		}
	}
	int query(int x){
		int ans = 0;
		for(; x; x -= lowbit(x)){
			ans = max(c[x], ans);
		}
		return ans;
	}
	#undef lowbit
}BIT;

int main(){
#ifdef FILE_IO
	start;
#endif
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1, w, v; i <= n; i++){
			scanf("%d%d", &w, &v);
			things[i] = thing(w, v);
		}
		scanf("%d", &m);
		for(int i = 1, w; i <= m; i++){
			scanf("%d", &w);
			bags[i] = w;
		}
		sort(things + 1, things + n + 1, thingCmp());
		sort(bags + 1, bags + m + 1, greater<int>());
		int end = 1, begin = 1;
		for(int i = n, j = n - 1, cnt = 1; i > 0; i = j, j = i - 1, BIT.big = cnt++){
			while(things[i].value == things[j].value) j--;
			for(int k = i; k > j; k--) things[k].value = cnt;
		}
		sort(things + 1, things + n + 1);
		while(bags[begin] < things[1].weight) ++begin;
		BIT.clear();
		BIT.big++;
		ans = 0;
		for(int i = 1; i <= n; i++){
			while(bags[end] < things[i].weight) ++end;
			int x = BIT.query(things[i].value) + 1;
			ans = max(ans, min(x, max(end - begin + 1, 0)));
			BIT.update(things[i].value + 1, x);
		}
		printf("%d\n", ans);
	}
	return 0;
}
