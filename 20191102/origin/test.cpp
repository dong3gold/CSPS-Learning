#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <set>

using namespace std;

set<int> q[1000];

int main(){
	for(int i = 0; i < 999;){
		q[i].insert(i);
		i++;
		q[i] = q[i-1];
	}
	printf("%d", q[999].size());
	return 0;
}

