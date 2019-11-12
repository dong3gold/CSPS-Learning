#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>

//#define FILE_IO
#ifdef FILE_IO
#define FILE triangle
#define to_in(x) #x ".in"
#define to_out(x) #x ".out"
#define mask_in(x) to_in(x)
#define mask_out(x) to_out(x)
#define start freopen(mask_in(FILE), "r", stdin)//, freopen(mask_out(FILE), "w", stdout)
#endif

using namespace std;

struct point
{
	int x, y;
	point(int x = -1, int y = -1) : x(x), y(y) {}
	bool operator<(const point &rhs) const { return y > rhs.y; }
} points[3010], ch[3010];

typedef point vector;

vector operator-(const point &x, const point &y)
{
	return vector(x.x - y.x, x.y - y.y);
}

int dot(const vector &x, const vector &y) { return x.x * y.x + x.y * y.y; }
double length(const vector &x) { return sqrt(dot(x, x)); }
int cross(const vector &x, const vector &y) { return x.x * y.y - x.y * y.x; }

long long ans;
int n, r[3010];
double Angle[3010];

bool cmp(int a, int b)
{
	return Angle[a] < Angle[b];
}

int main()
{	
#ifdef FILE_IO
	start;
#endif
	scanf("%d", &n);
	for (int i = 0, x, y; i < n; i++){
		scanf("%d %d", &x, &y); points[i] = point(x, y);
	}
		
	sort(points, points + n);
	for (int i = 2; i < n; i++)
	{
		for (int j = 0; j < i; j++)
			ch[j] = points[j] - points[i], Angle[j] = atan2(ch[j].y, ch[j].x), r[j] = j;
		sort(r, r + i, cmp);
		long long sumx = ch[r[0]].x, sumy = ch[r[0]].y;
		for (int k = 1; k < i; k++)
		{
			ans += sumx * ch[r[k]].y - sumy * ch[r[k]].x;
			sumx += ch[r[k]].x, sumy += ch[r[k]].y;
		}
	}
	if (ans & 1)
		printf("%lld.5\n", ans / 2);
	else
		printf("%lld.0\n", ans / 2);
	return 0;
}