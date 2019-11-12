//https://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Other-Builtins.html built-in functions provided by GCC 的介绍
#include <cstdio>
typedef unsigned int U;
const int N = 3010, M = 100010, BUF = 72000000;
char Buf[BUF], *buf = Buf;
int n, m, K, lim, i, j, k, u, d, a[N][N], cnt[M], s[N], mx;
long long ans;
bool in[N][N], ou[N][N];//矩阵上边与下边。
//F数组，原题中有说每个数权值小于M(100000);
//这里的f第一维为颜色，第二位为
U f[M][N / 32 + 5];
/*
inline void read(int &a)
{
	for (a = 0; *buf < 48; buf++) ;
	while (*buf > 47) a = a * 10 + *buf++ - 48;
}
*/
void read(int &a){ char ch(0);
	while(ch<48)ch=getchar();
	while(ch>47){a=a*10+(ch^48);ch=getchar();}
}

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }
inline void add(U *f, int x)
{
	int y = x >> 5, pre = -1, suf = -1; //x>>5即x当前所在段。
	if (f[y])
	{
		int o = x & 31;
		U z = f[y];
		for (int i = o - 1; ~i; i--)
			if (z >> i & 1)
			{
				pre = y << 5 | i;
				break;
			}
		for (int i = o + 1; i < 32; i++)
			if (z >> i & 1)
			{
				suf = y << 5 | i;
				break;
			}
	}
	if (pre < 0) //如果在当前段内没找到,往下1段找。
		for (int i = y - 1; ~i; i--)
			if (f[i])
			{
				pre = i << 5 | (31 - __builtin_clz(f[i])); //clz()前导零的个数, 31减去后即头位1的位置，也即前驱
				break;
			}
	if (suf < 0)
		for (int i = y + 1; i <= lim; i++)
			if (f[i])
			{
				suf = i << 5 | __builtin_ctz(f[i]); //ctz()末尾零的个数,即末位1的位置，后继
				break;
			}
	int l = max(pre + 1, x - K + 1), r = min(x, suf - K);//这个点出来时，影响范围为[x-K+1,x]，分别与前后继比较，得出实际更新区间。
	if (l <= r)
		s[l]++, s[r + 1]--;
	f[y] ^= 1U << (x & 31); //对应段内加入j。
}
inline void del(U *f, int x)
{
	int y = x >> 5, pre = -1, suf = -1;
	f[y] ^= 1U << (x & 31); //同上，删除对应的j。
	if (f[y])
	{
		int o = x & 31;
		U z = f[y];
		for (int i = o - 1; ~i; i--)
			if (z >> i & 1)
			{
				pre = y << 5 | i;
				break;
			}
		for (int i = o + 1; i < 32; i++)
			if (z >> i & 1)
			{
				suf = y << 5 | i;
				break;
			}
	}
	if (pre < 0)
		for (int i = y - 1; ~i; i--)
			if (f[i])
			{
				pre = i << 5 | (31 - __builtin_clz(f[i]));
				break;
			}
	if (suf < 0)
		for (int i = y + 1; i <= lim; i++)
			if (f[i])
			{
				suf = i << 5 | __builtin_ctz(f[i]);
				break;
			}
	int l = max(pre + 1, x - K + 1), r = min(x, suf - K);
	if (l <= r)
		s[l]--, s[r + 1]++;
}
int main()
{
	//fread(Buf, 1, BUF, stdin);
	read(n), read(m), read(K);
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			read(a[i][j]);
	for (j = 1; j <= m; j++) //计算颜色的并，确定颜色正方形的上下边。
	{
		for (d = 1; d < K; d++)
			if (!(cnt[a[d][j]]++))
				in[d][j] = 1;
		for (u = 0; d <= n; u++, d++)
		{
			if (u)
				if (!(--cnt[a[u][j]]))
					ou[u][j] = 1;
			if (!(cnt[a[d][j]]++))
				in[d][j] = 1;
		}
		for (i = 1; i <= n; i++)
			cnt[a[i][j]] = 0;
	}
	lim = (m + 1) >> 5; //右移5即除32
	for (i = 1; i < M; i++)
	{
		f[i][0] = 1;
		f[i][(m + 1) >> 5] |= 1U << ((m + 1) & 31); //每5位压到1位，这里在初始化，右和左各标上1，方便判断。
	}
	//for(int i = 1; i <= n; i++, printf("\n")) for(int j = 1; j <= m; j++) printf("%d ", in[i][j]);
	//初始加边
	for (d = 1; d < K; d++)
		for (j = 1; j <= m; j++)
			if (in[d][j])
				add(f[a[d][j]], j);
	//扫描线，碰到上边就删边，碰到下边加边，扫描线上从左自右枚举点，计算贡献。
	for (u = 0; d <= n; u++, d++) 
	{
		if (u)
			for (j = 1; j <= m; j++)
				if (ou[u][j])
					del(f[a[u][j]], j);
		for (j = 1; j <= m; j++)
			if (in[d][j])
				add(f[a[d][j]], j);
		for (j = 1, k = 0; j + K - 1 <= m; j++)
		{
			k += s[j];
			if (k > mx)
				mx = k;
			ans += k;
		}
	}
	return printf("%d %lld", mx, ans), 0;
}
