#include<cstdio>
#include<algorithm>
using namespace std; 
struct node{
    int y,next; 
}a[200001];
int len,n,last[200001],f[200001],g[200001]; bool b[200001]; 
void dp(int k)
{
    int q=1,w=0; 
    for (int i=last[k];i;i=a[i].next)
    {
        if (!b[a[i].y]) {
            b[a[i].y]=1; 
            dp(a[i].y); 
            q+=min(f[a[i].y],g[a[i].y]);
        } 
        w+=g[a[i].y]; 
    }
    g[k]=q; 
    f[k]=w; 
}
int main()
{
    scanf("%d",&n); 
    int x,z;
    for (int i=1;i<=n;i++)
     {
        scanf("%d",&z); 
        for (int j=1;j<=z;j++)
        {
           scanf("%d",&x);  
           a[++len]=(node){x,last[i]}; last[i]=len; 
        }
     }
    b[1]=1; dp(1); 
    printf("%d",min(f[1],g[1])); 
}
