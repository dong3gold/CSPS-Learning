#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>

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


int main(){
#ifdef FILE_IO
	start;
#endif
	srand(time(NULL));
	cout << (1LL * rand() << 32 ^ rand() << 16 ^ rand()) % 2148473648LL << 0;
	return 0;
}