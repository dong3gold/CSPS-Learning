#include <cstdio>
#include <algorithm>
#include <queue>
#include <cctype>
#include <cstring>
#define allDirection (int i = 0; i < 4; i++)
#define able (x + vec[i][0] >= 0 && x + vec[i][0] < C && y + vec[i][1] >= 0 && y + vec[i][1] < R && !rock[y + vec[i][1]][x + vec[i][0]])
#define flooded (floodedTime[y + vec[i][1]][x + vec[i][0]] != 0 && floodedTime[y + vec[i][1]][x + vec[i][0]] <= t + 1) 
#define Flooded (floodedTime[y][x])
#define Water (floodedTime[y + vec[i][1]][x + vec[i][0]])
#define floodThrough q.push(make_pair(make_pair(x + vec[i][0], y + vec[i][1]), t+1))
#define nextStep State now = q.front(); q.pop(); int x = now.first.first, y = now.first.second, t = now.second
#define IwontGoBackAgain continue
#define NowICanSleep printf("%d\n", t); return 
#define KAKTUS printf("KAKTUS\n"); return 
#define StartWalk q.push(make_pair(make_pair(sx, sy), 0))
#define NextState ((x + vec[i][0]), (y + vec[i][1]), t)
#define Home (x == Dx && y == Dy)
#define tryNextStep q.push(make_pair(make_pair(x + vec[i][0], y + vec[i][1]), t + 1))
#define FloodStart for(int i = 0; i < tot; i++) q.push(make_pair(make_pair(fld[i][0], fld[i][1]), 0))
#define canFlood !q.empty()
#define HaveWay !q.empty()
#define Fakenews (tot == 0)
#define wheresTheFlood State now = q.front(); q.pop(); int x = now.first.first, y = now.first.second, t = now.second
#define FloodwontFloodTwice continue
#define WhyCantFloodDestoryAHome continue
#define heresFlood floodedTime[y][x] = t;

using namespace std;
char read(){
	char ch = 0;
	while(!isprint(ch) || ch == 32){ch = getchar();} 
	return ch;
}

typedef pair<pair<int, int>, int> State;
int floodedTime[55][55];
bool rock[55][55];
int fld[500][2], tot = 0;
const int vec[4][2] = {{0, 1},{-1, 0},{0, -1},{1, 0}};
int R, C;
int Dx, Dy;
int Sx, Sy;

void flood(){
	queue<State > q;
	if(not Fakenews){
		FloodStart;
		while(canFlood){
			wheresTheFlood;
			if(Flooded) FloodwontFloodTwice;
			if(Home) WhyCantFloodDestoryAHome;
			heresFlood;
			for allDirection {
				if(able and not Water){
					floodThrough;
				}
			}
		}
	}
}
bool walked[55][55];
void walk(int sx, int sy){
	queue <State > q;
	StartWalk;
	while(HaveWay){
		nextStep;
		if(walked[x][y]) IwontGoBackAgain;
		if(Home) {
			NowICanSleep;
		}
		walked[x][y] = 1;
		for allDirection {
			if(able and not flooded){
				tryNextStep;
			}
		}
	}
	KAKTUS;
}
int main(){
	scanf("%d%d", &R, &C); char ch;
	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			ch = read();
			if(ch == 'X') rock[i][j] = 1;
			else if(ch == '*') {
				fld[tot][0] = j;
				fld[tot++][1] = i;
			}
			else if(ch == 'D'){
				Dx = j; Dy = i;
			}
			else if(ch == 'S'){
				Sx = j; Sy = i;
			}
		}
	}
	flood();
	walk(Sx, Sy);
	return 0;
}
