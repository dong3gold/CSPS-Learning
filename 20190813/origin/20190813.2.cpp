#include <cstdio>
#include <vector>
#include <cstdlib>
using namespace std;
char ch[100][100];
int tot = 0, a = 0;
int main(){
	for(int i = 0; i < 20; i++){
		ch[0][i] = ch[19][i] = '#';
		ch[i][0] = ch[i][19] = '#';
		ch[i][20] = '\n';
	}
	for(int i = 1; i < 19; i++){
		for(int j = 1; j < 19; j++){
			ch[i][j] = ' ';
		}
	}
	while(1){
		for(int i = 0; i < 32; i++){
			printf("%s", ch[i]);
		}
		ch[tot/18 + 1][tot%18 + 1] = a + 48;
		if(tot < 324) tot++;
		else{
			tot = 0;
			if(a < 10) a++;
			else a = 0;
		}
		system("cls");
	}
	return 0;
}
