#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cctype>
using namespace std;
bool tub[256][3][3]; //tub[type][x + 1][y + 1]
char mp[30][30];
int vis[30][30];
int vec[4][2];
int xm, ym, xz, yz;
int R, C;
queue<pair<int, int> > qm;
queue<pair<int, int> > qz;
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
void bfsz(int xz, int yz){
	if(vis[xz][yz] == 1 || xz < 0 || yz < 0 || xz >= C || yz >= R) return ;
	qz.push(make_pair(xz, yz));
	while(!qz.empty()){
		auto tmp = qz.front(); qz.pop();
		int x = tmp.first, y = tmp.second;
		vis[x][y] = 1;
		if(mp[x][y] != '+')
			for(int i = 0; i < 4; i++){
				if(tub[mp[x][y]][vec[i][0]][vec[i][1]]){
					bfsz(x + vec[i][0] - 1, y + vec[i][1] - 1);
				}
		}
		else if(mp[x][y] == '+'){
			for(int i = 0; i < 4; i++){
				if(x + vec[(i+2)%4][0] - 1 >= 0 && y + vec[(i+2)%4][1] - 1 >= 0 && vis[x + vec[(i+2)%4][0] - 1][y + vec[(i+2)%4][1] - 1] == 1){
					bfsz(x + vec[i][0] - 1, y + vec[i][1] - 1);
				}
			}
		}
	}
}
bool flag = 0;

void check(int x, int y){
	int a[4]; char ans;
	for(int i = 0; i < 4; i++){
		if(x+vec[i][0]-1>=0 && y+vec[i][1]-1 >= 0)
			a[i] = vis[x+vec[i][0]-1][y+vec[i][1]-1];
	}
	if(a[0] == a[2] && a[1] == a[3] && a[0]+a[1]==3) ans = '+', flag = 1;
	else if(a[0] == a[2] && a[0] == 0 && a[1] + a[3] == 3 ) ans = '-', flag = 1;
	else if(a[1] == a[3] && a[1] == 0 && a[0] + a[2] == 3) ans = '|', flag = 1;
	else if(a[2] == a[3] && a[2] == 0 && a[0] + a[1] == 3) ans = '1', flag = 1;
	else if(a[0] == a[3] && a[0] == 0 && a[1] + a[2] == 3) ans = '2', flag = 1;
	else if(a[0] == a[1] && a[0] == 0 && a[2] + a[3] == 3) ans = '3', flag = 1;
	else if(a[1] == a[2] && a[1] == 0 && a[0] + a[3] == 3) ans = '4', flag = 1;
	if(flag == 1){
		printf("%d %d %c\n",y+1, x+1, ans);
	}
}

void bfsm(int xm, int ym){
	if(vis[xm][ym] == 2 || xm < 0 || ym < 0 || xm >= C || ym >= R) return ;
	qm.push(make_pair(xm, ym));
	while(!qm.empty() && !flag){
		auto tmp = qm.front(); qm.pop();
		int x = tmp.first, y = tmp.second;
		if(mp[x][y] == '+'){
			for(int i = 0; i < 4; i++){
				if(x + vec[(i+2)%4][0] - 1 >= 0 && y + vec[(i+2)%4][1] - 1 >= 0 && vis[x + vec[(i+2)%4][0] - 1][y + vec[(i+2)%4][1] - 1] == 2 && !flag){
					vis[x][y] = 2;
					bfsm(x + vec[i][0] - 1, y + vec[i][1] - 1);
				}
			}
		}	
		else if(mp[x][y] != '+' && mp[x][y] != '.'){
			for(int i = 0; i < 4; i++){
				if(tub[mp[x][y]][vec[i][0]][vec[i][1]] && !flag){
					vis[x][y] = 2;
					bfsm(x + vec[i][0] - 1, y + vec[i][1] - 1);
				}
			}
		}
		else{
			if(vis[x][y] == 1) check(x, y);
		}
	}
}
int main(){
	init();
	read();
	bfsz(xz, yz);
	bfsm(xm, ym);
	return 0;
}
