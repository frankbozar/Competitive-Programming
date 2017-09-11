#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
const int N=1234;
vector<int> val(1<<16, -1), nxt(1<<16, 0);

void query(int pos)
{
    if( !nxt[pos] )
    {
        printf("? %d\n", pos);
        fflush(stdout);
        scanf("%d%d", &val[pos], &nxt[pos]);
    }
}

int main()
{
    int n, idx, k;
    scanf("%d%d%d", &n, &idx, &k);
    query(idx);
    
    for(int i=0; i<N; i++)
    {
        int pos=rand()*(long long)rand()%n+1;
        query(pos);
        
        if( val[idx]<val[pos] && val[pos]<=k )
            idx=pos;
    }
    
    for(; idx>0; idx=nxt[idx])
    {
        query(idx);
        
        if( val[idx]>=k )
            break;
    }
    
    printf("! %d\n", idx<0 ? -1 : val[idx]);
}


/*
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1800;
vector<int> val(1<<16, -1), nxt(1<<16, 0), pic(1<<16, -1);

void query(int pos, int sts)
{
    if( pic[pos]>=sts )
        return ;
    
    pic[pos]=1;
    printf("? %d\n", pos);
    fflush(stdout);
    scanf("%d%d", &val[pos], &nxt[pos]);
    
    if( val[pos]<0 )
        exit(0);
    
    if( nxt[pos]>0 )
        pic[ nxt[pos] ]=max(pic[ nxt[pos] ], 0);
}

int main()
{
    srand(0xE04);
    int n, idx, k;
    scanf("%d%d%d", &n, &idx, &k);
    query(idx, 0);
    
    for(int i=0; i<N; i++)
    {
        int pos=rand()%n+1;
        query(pos, 0);
        
        if( val[idx]<val[pos] && val[pos]<=k )
            idx=pos;
    }
    
    while( idx>0 )
    {
        query(idx, 1);
        
        if( val[idx]>=k )
            break;
        
        idx=nxt[idx];
    }
    
    printf("! %d\n", idx<0 ? -1 : val[idx]);
    fflush(stdout);
}
*/
