#include <cstdio>
using namespace std;
int main(){
	int n;
	scanf("%d", &n);
	switch(n) {
		case 1 : {
			printf("1\n");
			break;
		}
		case 2 : {
			printf("2\n");
			break;
		}
		case 3 : {
			printf("3\n");
			break;
		}
		default: {
			printf("%d\n", n*(n+1));
			break;
		}
	}
}
