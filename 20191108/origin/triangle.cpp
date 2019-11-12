#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>

//#define FILE_IO
#ifdef FILE_IO
	#define FILE triangle
	#define to_in(x) #x".in"
	#define to_out(x) #x".out"
	#define mask_in(x) to_in(x)
	#define mask_out(x) to_out(x)
	#define start freopen(mask_in(FILE), "r", stdin), freopen(mask_out(FILE), "w", stdout)
#endif


struct point
{
	int x, y;
	point(int x = -1, int y = -1):x(x),y(y){}
	bool operator< (const point& rhs) const {return x == rhs.x ? y < rhs.y : x < rhs.y;}
}points[3010], ch[3010];

typedef point vector;

vector operator- (const point& x, const point& y){
	return vector(x.x - y.x, x.y - y.y);
}

int dot(const vector& x, const vector& y) {return x.x * y.x + x.y * y.y;}
double length(const vector& x){return sqrt(dot(x, x));}
int cross(const vector& x, const vector& y){return x.x * y.y - x.y * y.x;}


int ConvexHull(point *p, int n, point *ch){
	std::sort(p, p + n);
	int m = 0;
	for(int i = 0; i < n; i++){
		while(m > 1 && cross(ch[m-1] - ch[m - 2], p[i] - ch[m - 2]) < 0) m--;
		ch[m++] = p[i];
	}
	int k = m;
	for(int i = n - 2; i >= 0; i--){
		while(m > k && cross(ch[m - 1] - ch[m - 2], p[i] - ch[m-2]) < 0) m--;
		ch[m++] = p[i];
	}
	if(n > 1) m--;
	return m;
}

double area(point *p, int n){
	double ans = 0;
	for(int i = 0; i < n - 1; i++){
		ans += cross(p[i] - p[0], p[i+1] - p[0]);
	}
	return ans / 2;
}

int n;

int main(){
	std::scanf("%d", &n);
	for(int i = 0, x, y; i < n; i++){
		std::scanf("%d%d", &x, &y);
		points[i] = point(x, y);
	}
	int m = ConvexHull(points, n, ch);
	double ans = area(ch, m) * m;
	for(int i = 0; i < m - 2; i++) 
		ans -= (double)cross(ch[i+1] - ch[i], ch[i+2] - ch[i+1]) / 2;
	ans -= (double)cross(ch[m-1] - ch[m-2], ch[0] - ch[m-1]) / 2;
	ans -= (double)cross(ch[0] - ch[m-1], ch[1] - ch[0]) / 2;
	std::printf("%lf\n", ans);
	return 0;
}
