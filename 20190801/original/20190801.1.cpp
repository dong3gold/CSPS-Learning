#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>

using namespace std;
vector<int> G[58];
int a[58], tot = 7, deep = 1;
int id[6];
void work(int n){
	if(n == 1){
		printf("1\n");
		return;
	}
	if(tot >= n){
		int i = 0;
		while(n - a[i] > 0) i++; i--;
		printf("%d\n", G[i+1][n-a[i]-1]);
		return;
	}
	int last;
	while(tot < n){
		if(tot == a[deep]){
			last = G[deep][tot-a[deep-1]-1];
			tot++, deep++;
		}
		else{
			last = G[deep][tot-a[deep-1]-1];
			tot++;
		}
		int e = (tot - a[deep - 1]) / deep;
		int b = (tot - a[deep - 1]) % deep;
		if(b){
			int min = 0;
			for(int i = 1; i < 6; i++){
				if(!(i == last) && !(i == G[deep - 1][e*(deep-1)+b]) && !(i == G[deep - 1][e*(deep-1)+b-1]) && id[i] < id[min]) min = i; 
			}
			G[deep].push_back(min);
			id[min]++;
		}
		else{
			int min = 0;
			for(int i = 1; i < 6; i++){
				if(!(i == last) && !(i == G[deep - 1][e*(deep-1)+b]) && id[i] < id[min]) min = i; 
			}
			G[deep].push_back(min);
			id[min]++;
		}
	}
	printf("%d\n", G[deep][tot-a[deep-1]-1]);
}
int main(){
	int T, n;
	a[0] = 1;
	for(int i = 1; i < 58; i++){
		a[i] = a[i - 1] + 6 * i;
	}
	G[0].push_back(1);
	G[1].push_back(2);
	G[1].push_back(3);
	G[1].push_back(4);
	G[1].push_back(5);
	G[1].push_back(2);
	G[1].push_back(3);
	id[1] = 1; id[2] = 2; id[3] = 2; id[4] = 1; id[5] = 1; id[0] = 0x7f7f7f;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		work(n);
	}
	return 0;
}
