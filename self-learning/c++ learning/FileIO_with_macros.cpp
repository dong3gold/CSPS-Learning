#include <cstdio>
using namespace std;
#define FILE_IO
#define FILE test

#ifdef FILE_IO
/*
#define to_string(x) (#x)
#define FILE_IN FILE##.in
#define FILE_OUT FILE##.out
#define start freopen(to_string(FILE_IN), "r", stdin), freopen(to_string(FILE_OUT), "w", stdout)
these will fail because ## which "Only tokens that form a valid token together may be pasted"
*/
/*
#define to_in(x) (#x".in")
#define to_out(x) (#x".out")
#define in freopen(to_in(FILE), "r", stdin)
#define out freopen(to_out(FILE), "w", stdout)
these will fail because "FILE" the string itself directly passed into to_in() ans to_out
*/
#define to_in(x) (#x".in")
#define to_out(x) (#x".out")
#define mask_in(x) to_in(x)
#define mask_out(x) to_out(x)
#define in freopen(mask_in(FILE), "r", stdin)
#define out freopen(mask_out(FILE), "w", stdout)
/*
So, what make it possible is that we use another macros mask_xx
to replace the symbol FILE with the word "test"(it still not string)
before it passed into the to_xx 
*/
#endif

char s[1000];

int main(){
    if(in == NULL) {
        printf("Failed to read from File\"%s\".", mask_in(FILE));
        return -1;
    }
    if(out == NULL){
        printf("Failed to write to File\"%s\".", mask_out(FILE));
        return -2;
    }
    scanf("%s", s);
    printf("%s", s);
    printf(", is there any word else?\n");
    return 0;
}