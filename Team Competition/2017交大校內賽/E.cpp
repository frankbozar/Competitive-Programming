#include<cstdio>
#include<stack>
#include<vector>
using namespace std;
typedef long long lld;
#define data pair<int,int>
#define v first
#define p second

vector<int> fail(vector<int> s)
{
    int m=s.size();
    vector<int> f(m+1, -1);

    for(int k, i=1; i<=m; i++)
    {
        for(k=f[i-1]; k>=0 && s[k]!=s[i-1]; k=f[k]);
        f[i]=k+1;
    }

    return f;
}

int func(int k, int v, const vector<int>& s, const vector<int>& f)
{
    for(; ; k=f[k])
    {
        if( k==-1 )
            return 0;
        else if( (v&1)==s[k] )
            return k+1;
    }
}

void sol(int n, int m, const vector<int>& s)
{
    const vector<int> f=fail(s);
    stack<data> S;
    S.push(data(0, 0));

    for(bool err=false; n>0; n--)
    {
        char op[8]={0};
        scanf("%s", op);
        int v;

        if( op[1]=='U' )
            scanf("%d", &v);

        if( err )
            continue;
        else if( op[1]=='U' )
        {
            int k=func(S.top().p, v, s, f);
            S.push(data(v, k));
        }
        else if( op[1]=='O' )
        {
            if( S.size()==1 )
            {
                printf("ERROR\n");
                err=true;
            }
            else
            {
                printf("%d\n", S.top().v);
                S.pop();
            }
        }
        else if( op[1]=='M' )
        {
            for(; S.size()>1; S.pop());
        }
        else
        {
            if( S.size()<3 )
            {
                printf("ERROR\n");
                err=true;
            }
            else
            {
                lld x=S.top().v;
                S.pop();
                lld y=S.top().v;
                S.pop();
                lld v=x+y;

                int k=func(S.top().p, v, s, f);
                S.push(data(v, k));
            }
        }

        if( S.top().p==m )
        {
            printf("ERROR\n");
            err=true;
        }
    }
}

int main()
{
    int ncase;
    scanf("%d", &ncase);

    for(int cases=1; cases<=ncase; cases++)
    {
        printf("CASE %d:\n", cases);
        int n, m;
        scanf("%d%d", &m, &n);
        vector<int> s(m);

        for(int i=m-1; i>=0; i--)
            scanf("%d", &s[i]);

        sol(n, m, s);
    }
}

/*

2
3 4
1 1 1
PUSH 2147483647
PUSH 2147483647
ADD
POP

3 4
1 1 1
PUSH -2147483647
PUSH -2147483647
ADD
POP

*/

/*

3

2 5
0 0
PUSH 3
PUSH 5
ADD
POP
POP

2 3
0 0
PUSH 2
PUSH 4
ADD

2 5
0 0
PUSH 2
EMPTY
PUSH 4
PUSH 5
POP

*/
