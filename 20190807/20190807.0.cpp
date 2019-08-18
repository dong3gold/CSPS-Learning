#include <cstdio>
#include <vector>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
int read(){
	int X = 0, w = 0; char ch = 0;
	while(!isdigit(ch)){w |= ch == '-'; ch = getchar();}
	while(isdigit(ch)){X = (X<<3) + (X<<1) + (ch^48); ch = getchar();}
	return w ? -X : X;
}
struct point{
	int x, y;
	point():x(0),y(0){}
	point(int x, int y):x(x),y(y){}
	point operator + (const point& _p){
		point _point;
		_point.x = this->x + _p.x;
		_point.y = this->y + _p.y;
		return _point;
	} 
	point operator - (const point& _p){
		point _point;
		_point.x = this->x - _p.x;
		_point.y = this->y - _p.y;
		return _point;
	}
	int operator * (const point& _p) const{
		return (this->x * _p.x) + (this->y * _p.y);
	}
	bool operator == (const point& _p) const{
		return (this->x * _p.y) == (this->y * _p.x); 
	}
	bool cross(const point& _p) const{
		return (*this) * _p == 0;
	}
};
point points[1600];
point lines[1520][1520];

int n;
int main(){
	n = read();
	for(int i = 0; i < n; i++){
		points[i] = point(read(), read());
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			lines[i][j] = points[j] - points[i];
		}
	}
	int sum = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i != j)
			for(int k = j + 1; k < n; k++){
				if(i != k && j != k) if(lines[i][j].cross(lines[i][k])) sum++;
			}
		}
	}
	printf("%d\n", sum);
}
