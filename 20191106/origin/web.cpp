#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <queue>

#define FILE_IO
#ifdef FILE_IO
	#define FILE web
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif

using namespace std;

int main(){
#ifndef LOCAL
	#ifdef FILE_IO
		start;
	#endif
#endif
	printf("Impossible\n");
	return 0;
}
