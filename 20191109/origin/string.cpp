#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;
typedef unsigned long long ull;
template <ull Base, ull mod>
struct Hash
{
	char s[50020][102]; ull hash[50020][102]; int len[50020];
	ull mi[110];
	ull hash_value(const int &t, const int& x, const int& y){
		if(x == 0) return hash[t][y];
		return (hash[t][y] - hash[t][x-1] * mi[y - x + 1] % mod + mod) % mod;
	}
	void Make_Hash(int n){
		mi[0] = 1;
		for(int i = 1; i < 101; i++){
			mi[i] = mi[i-1] * Base % mod;
		}
		for(int i = 0; i < n; i++){
			hash[i][0] = s[i][0];int j = 1;
			for(;s[i][j]; j++){
				hash[i][j] = (hash[i][j-1] * Base % mod + s[i][j]) % mod;
			}
			len[i] = j;
		}
	}

	char a[102], b[102]; ull hash_a, hash_b; int len_a, len_b;
	void make(){
		hash_a = a[0];
		int i = 1;
		for(; a[i]; i++){
			hash_a = (hash_a * Base % mod + a[i]) % mod;
		}
		len_a = i;
		hash_b = b[0];
		i = 1;
		for(; b[i]; i++){
			hash_b = (hash_b * Base % mod + b[i]) % mod;
		}
		len_b = i;
	}

	int query(int n){
		int ans = 0;
		for(int i = 0; i < n; i++){
			if(hash_value(i, 0, len_a-1) == hash_a && hash_value(i, len[i] - len_b, len[i] - 1) == hash_b)
				ans++;
		}
		return ans;
	}
};


Hash<19260817ULL, 1000000009ULL> hashTable;

int n, q;

int main(){
	scanf("%d%d", &n, &q);
	for(int i = 0; i < n; i++){
		scanf("%s", hashTable.s[i]);
	}
	hashTable.Make_Hash(n);
	for(int i = 0; i < q; i++){
		scanf("%s%s", hashTable.a, hashTable.b);
		hashTable.make();
		printf("%d\n", hashTable.query(n));
	}
	return 0;
}

