#include <cstdio>
using namespace std;
int i = 0; int j = 4;
int f1(){
	printf("f1 ");
	return ++i; 
}
int f2(){
	printf("f2 ");
	return ++i;
}
int f3(){
	printf("f3 ");
	return ++i;
}
void print(int a, int b, int c){
	printf("\n %d  %d  %d", a, b, c);
}
void print(int a, int b, int c, int d){
	printf("\n%d %d %d %d", a, b, c, d);
}
int main(){
	int a = 10;
	print(f3(),f2(),f1());
	print(j++, j++, j++);
	printf("%d %d %d %d", a++, ++a, a, a++);
	return 0;
}
