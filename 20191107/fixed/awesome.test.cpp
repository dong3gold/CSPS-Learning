#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <map>
#include <tuple>
#include <unordered_set>
#define FILE_IO
#ifdef FILE_IO
	#define FILE awesome
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif

using namespace std;
long long n, p;
long long a[2444], cnt = 0;
long long ans = 0;
struct TupleHash{
    size_t operator() (tuple<long long, long long, long long> const &t) const {
        size_t a = hash<long long>{}(get<0>(t));
        size_t b = hash<long long>{}(get<1>(t));
        size_t c = hash<long long>{}(get<2>(t));
        return a ^ (b << 1) ^ (c << 3);
    }
};
unordered_set<tuple<long long, long long, long long>, TupleHash> s;

int main(){
#ifdef FILE_IO
	start;
#endif
	scanf("%lld%lld", &n, &p);
	for(int i = 0; i < n; i++){
		scanf("%lld", i + a);
	}
	sort(a, a + n);
    for(long long i = 0L; i < n; i++){
        for(long long j = i + 1L; j < n; j++){
            for(long long k = j + 1L; k < n; k++){
                if(a[i] * a[j] % p * a[k] % p == 1 && s.find(make_tuple(a[i], a[j], a[k])) == s.end()){
                    printf("%lld * %lld = %lld, %lld\n", a[i], a[j], a[i] * a[j] % p, a[k]); s.insert(make_tuple(a[i], a[j], a[k]));
                    ans++;
                }
            }
        }
    }
	printf("%lld\n", ans);
	return 0;
}
