#include <cstdio>
#include <iostream>
using namespace std;
int n, k, num, x, y;
struct point{
	int X, Y;
	point():X(0),Y(0){}
	point(int X, int Y):X(X),Y(Y){}
	point operator + (const point& x) {
		point _point;
		_point.X = (this->X + x.X + n) %n ? (this->X + x.X + n) % n : n;
		_point.Y = (this->Y + x.Y + n) %n ? (this->Y + x.Y + n) % n : n;
		return _point;
	}
	bool operator == (const point& x) const{
		return this->X == x.X && this->Y == x.Y;
	}
	point operator - (const point& x){
		point _point;
		_point.X = (this->X - x.X + n) % n ;
		_point.Y = (this->Y - x.Y + n) % n ;
		return _point;
	}
	explicit operator int(){
		return this->X + this->Y;
	}
#ifdef debug
	friend ostream &operator<<( ostream &output, const point &P )
    { 
         output << "X : " << P.X << " Y : " << P.Y;
         return output;            
    }
#endif
};
struct query{
	int num;
	point from, to;
	query():num(0),from(0,0),to(0,0){}
	query(int num, int X, int Y):num(num),to(X,Y),from(num%n?num%n:n, (num-1)/n+1){}
} q[1002];
int main(){
	int sum = 0;
	scanf("%d%d", &n, &k);
	for(int i = 0; i < k; i++){
		scanf("%d%d%d", &num, &x, &y);
		q[i] = query(num, y, x);
	}
	for(int i = 0; i < k; i++){
		for(int j = 0; j < i; j++){
			if(q[i].num == q[j].num){
				q[i].from = q[j].to;
			}
			else{
				if(q[i].from.Y == q[j].from.Y){
					q[i].from = q[i].from + point(q[j].to.X - q[j].from.X, 0);
				}
				else if(q[i].from.X == q[j].to.X){
					q[i].from = q[i].from + point(0, q[j].to.Y - q[j].from.Y); 
				}
			}
		}
#ifdef debug
		cout << "Num: " << q[i].num << " " << q[i].from << endl;
#endif
		printf("%d\n", (int)(q[i].to - q[i].from));
	}
	return 0;
}
