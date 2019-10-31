#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cctype>
#define allDerict (int i = 0; i < 4; i++)
#define a(i) tub[mp[x + vec[i][0] - 1][y + vec[i][1] - 1]][vec[(i+2)%4][0]][vec[(i+2)%4][1]]
using namespace std;
bool tub[128][3][3]; //tub[type][x + 1][y + 1]
char mp[30][30];
int vis[30][30];
char mis[2][2][2][2];
int vec[4][2];
int xm, ym, xz, yz;
int R, C;
void init(){
	tub['|'][1][2] = 1;
	tub['|'][2][1] = 0;
	tub['|'][1][0] = 1;
	tub['|'][0][1] = 0;
	tub['-'][1][2] = 0;
	tub['-'][2][1] = 1;
	tub['-'][1][0] = 0;
	tub['-'][0][1] = 1;
	tub['+'][1][2] = 1;
	tub['+'][2][1] = 1;
	tub['+'][1][0] = 1;
	tub['+'][0][1] = 1;
	tub['1'][1][2] = 1;
	tub['1'][2][1] = 1;
	tub['1'][1][0] = 0;
	tub['1'][0][1] = 0;
	tub['2'][1][2] = 0;
	tub['2'][2][1] = 1;
	tub['2'][1][0] = 1;
	tub['2'][0][1] = 0;
	tub['3'][1][2] = 0;
	tub['3'][2][1] = 0;
	tub['3'][1][0] = 1;
	tub['3'][0][1] = 1;
	tub['4'][1][2] = 1;
	tub['4'][2][1] = 0;
	tub['4'][1][0] = 0;
	tub['4'][0][1] = 1;
	tub['Z'][1][2] = 1;
	tub['Z'][2][1] = 1;
	tub['Z'][1][0] = 1;
	tub['Z'][0][1] = 1;
	tub['M'][1][2] = 1;
	tub['M'][2][1] = 1;
	tub['M'][1][0] = 1;
	tub['M'][0][1] = 1;
	tub['.'][1][2] = 0;
	tub['.'][2][1] = 0;
	tub['.'][1][0] = 0;
	tub['.'][0][1] = 0;
	vec[0][0] = 1;
	vec[0][1] = 2;
	vec[1][0] = 2;
	vec[1][1] = 1;
	vec[2][0] = 1;
	vec[2][1] = 0;
	vec[3][0] = 0;
	vec[3][1] = 1;
	memset(mis, 0, sizeof(mis));
	mis[1][0][1][0] = '|';
	mis[0][1][0][1] = '-';
	mis[1][1][1][1] = '+';
	mis[1][1][0][0] = '1';
	mis[0][1][1][0] = '2';
	mis[0][0][1][1] = '3';
	mis[1][0][0][1] = '4';
}
char readChar(){
	char ch = 0;
	while(!isprint(ch)||ch==32) ch = getchar();
	return ch;
}
void read(){
	char ch;
	scanf("%d%d", &R, &C);
	for(int y = 0; y < R; y++){
		for(int x = 0; x < C; x++){
		mp[x][y] = ch = readChar(); 
		if(ch == 'M') xm = x, ym = y;
		else if(ch == 'Z') xz = x, yz = y;
		}
	}
}

bool flag = 0, nonPipe[128];
void check(int x, int y){
	if(mis[a(0)][a(1)][a(2)][a(3)] != 0) {
		printf("%d %d %c\n", y+1, x+1, mis[a(0)][a(1)][a(2)][a(3)]);
		flag = 1;
	}
}
void dfsz(int x, int y){
	if((mp[x][y] == '+' && vis[x][y] == 3) || (mp[x][y] != '+' && vis[x][y]) || x < 0 || y < 0 || x >= C || y >= R || flag) return;
	if(mp[x][y] == '+'){
		for allDerict {
			if(x + vec[i][0] - 1 >= 0 && y + vec[i][1] - 1 >= 0 && vis[x + vec[i][0] - 1][y + vec[i][1] - 1]){
				if(!vis[x][y]) vis[x][y] = (i&1) + 1;
				else vis[x][y] = 3;
				dfsz(x + vec[(i+2)%4][0] -1, y + vec[(i+2)%4][1] - 1);
			}
		}
	}
	else if(mp[x][y] == 'M' || mp[x][y] == 'Z'){
		vis[x][y] = 1;
		for allDerict {
			if(x + vec[i][0] - 1 >= 0 && y + vec[i][1] - 1 >= 0 && mp[x + vec[i][0] - 1][y + vec[i][1] - 1] != '.'){
				nonPipe[mp[x][y]] = 0;
				dfsz(x + vec[i][0] - 1, y + vec[i][1] - 1);
			}
		}
		if(nonPipe[mp[x][y]]) {
			for allDerict {
				if(tub[mp[x][y]][vec[i][0]][vec[i][1]]){
					dfsz(x + vec[i][0] - 1, y + vec[i][1] - 1);
			    }
			}
		}
	}
	else if(mp[x][y] != '.'){
		vis[x][y] = 1;
		for allDerict {
			if(tub[mp[x][y]][vec[i][0]][vec[i][1]]){
				dfsz(x + vec[i][0] - 1, y + vec[i][1] - 1);
			}
		}
	}
	else{
		check(x, y);
	}
}
int main(){
	init();
	read();
	dfsz(xz, yz);
	return 0;
}
