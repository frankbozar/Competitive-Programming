#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
char s[64][64];

struct SAT
{
    int n, m, rem, level;
    vector<vector<int>> C, CNT;//0: false, 1: true, 2: unassigned
    vector<int> UNIT, X, STAT;//0: unassigned, 1: decided, 2: implied
    vector<vector<vector<int>>> POS;//0: false, 1: true
    vector<vector<int>> I, ORDER;
    SAT(int _n, vector<vector<int>>& cnf) : n(_n), level(0), C(cnf), I(1){
        m=C.size(), rem=n;
        for(vector<int> &c : C) CNT.push_back({ 0, 0, (int)c.size() });
        X.resize(n + 1);
        STAT.assign(n + 1, 0);
        POS.assign(n + 1, { {}, {} });
        for(int i=0; i<m; i++) for(int x : C[i])
            POS[abs(x)][x < 0 ? 0 : 1].push_back(i);
        for(vector<int> &c : C) if( c.size()==1 )
            UNIT.push_back(c[0]);
        for(int i=1; i<=n; i++)
            ORDER.push_back({ (int)(POS[i][0].size() + POS[i][1].size()), i });
        sort(ORDER.rbegin(), ORDER.rend());
    }
    bool assign(int x, int val, int stat){//assumption: x is unassigned
        rem--, X[x]=val, STAT[x]=stat;
        bool res=true;
        for(int i=0; i<2; i++) for(int c : POS[x][i]){
            CNT[c][2]--, CNT[c][val==i]++;
            if( CNT[c][2]==1 && CNT[c][1]==0 )
                for(int y : C[c])
                    if( STAT[abs(y)]==0 ){
                        UNIT.push_back(y);
                        break;
                    }
            res&= !(CNT[c][1]==0 && CNT[c][2]==0);
        }
        return res;
    }
    void unassign(int x){//assumption: x is assigned
        rem++, STAT[x]=0;
        for(int i=0; i<2; i++)
            for(int c : POS[x][i])
                CNT[c][2]++, CNT[c][X[x]==i]--;
    }
    bool imply(){
        while( !UNIT.empty() ){
            int x=UNIT.back(), val=x>0;
            UNIT.pop_back();
            if( STAT[abs(x)]!=0 && X[abs(x)]==val ) continue;
            if( STAT[abs(x)]!=0 && X[abs(x)]!=val ) return false;
            I.back().push_back(abs(x));
            if (!assign(abs(x), val, 2)) return false;
        }
        return true;
    }
    void unimply(){
        for(int x : I.back()) unassign(x);
        I.back().clear();
    }
    bool sol(){
        if( !imply() ) return false;
        if( rem==0 ) return true;
        int x;
        for(int i=0; STAT[ x=ORDER[i][1] ]; i++);
        level++, I.push_back({});
        assign(x, rand()&1, 1);
        if( sol() ) return true;
        unassign(x), unimply(), UNIT.clear();
        assign(x, X[x]^1, 1);
        if( sol() ) return true;
        unassign(x), unimply();
        level--, I.pop_back();
        return false;
    }
};

struct data
{
    int x, y, d;
};

bool trace(vector<vector<int>>& cnf, vector<vector<vector<int>>>& pass, int id, int x, int y)
{
    int ok[2]={1, 1};
    
    for(int i=0; i<2; i++)
    {
        queue<data> Q;
        int used[64][64][4]={{{0}}};
        vector<data> pos;
        
        if( i==0 )
        {
            Q.push({x, y-1, 1});
            Q.push({x, y+1, 3});
        }
        else
        {
            Q.push({x-1, y, 0});
            Q.push({x+1, y, 2});
        }
        
        for(; !Q.empty(); Q.pop())
        {
            const data& D=Q.front();
            
            if( used[D.x][D.y][D.d] )
                continue;
            
            used[D.x][D.y][D.d]=1;
            
            if( s[D.x][D.y]=='#' )
                continue;
            else if( s[D.x][D.y]=='-' || s[D.x][D.y]=='|' )
            {
                ok[i]=false;
                break;
            }
            else if( s[D.x][D.y]=='\\' )
            {
                if( D.d==0 )
                    Q.push({D.x, D.y-1, 1});
                else if( D.d==1 )
                    Q.push({D.x-1, D.y, 0});
                else if( D.d==2 )
                    Q.push({D.x, D.y+1, 3});
                else//if( D.d==3 )
                    Q.push({D.x+1, D.y, 2});
            }
            else if( s[D.x][D.y]=='/' )
            {
                if( D.d==0 )
                    Q.push({D.x, D.y+1, 3});
                else if( D.d==1 )
                    Q.push({D.x+1, D.y, 2});
                else if( D.d==2 )
                    Q.push({D.x, D.y-1, 1});
                else//if( D.d==3 )
                    Q.push({D.x-1, D.y, 0});
            }
            else
            {
                pos.push_back({D.x, D.y, 0});
                
                if( D.d==0 )
                    Q.push({D.x-1, D.y, 0});
                else if( D.d==1 )
                    Q.push({D.x, D.y-1, 1});
                else if( D.d==2 )
                    Q.push({D.x+1, D.y, 2});
                else//if( D.d==3 )
                    Q.push({D.x, D.y+1, 3});
            }
        }
        
        if( ok[i] )
        {
            for(const data& D : pos)
            {
                if( used[D.x][D.y][0]>=0 )
                {
                    used[D.x][D.y][0]=-1;
                    pass[D.x][D.y].push_back(i ? id : -id);
                }
            }
        }
    }
    
    if( !ok[0] && !ok[1] )
        return false;
    else if( !ok[0] )
        cnf.push_back(vector<int>(1, id));
    else if( !ok[1] )
        cnf.push_back(vector<int>(1, -id));
    
    return true;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        memset(s, '#', sizeof(s));
        
        for(int i=1; i<=n; i++)
        {
            scanf("%s", &s[i][1]);
            s[i][m+1]='#';
        }
        
        int vars=0;
        bool ans=true;
        vector<vector<int>> cnf;
        vector<vector<vector<int>>> pass(n+1, vector<vector<int>>(m+1));
        
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                if( s[i][j]=='-' || s[i][j]=='|' )
                    if( !trace(cnf, pass, ++vars, i, j) )
                        ans=false;
        
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                if( s[i][j]=='.' )
                {
                    if( pass[i][j].empty() )
                        ans=false;
                    else
                        cnf.push_back(pass[i][j]);
                }
        
        if( !ans )
            printf("Case #%d: IMPOSSIBLE\n", cases);
        else
        {
            SAT S(vars, cnf);
            
            if( !S.sol() )
                printf("Case #%d: IMPOSSIBLE\n", cases);
            else
            {
                printf("Case #%d: POSSIBLE\n", cases);
                vars=0;
                
                for(int i=1; i<=n; i++)
                {
                    for(int j=1; j<=m; j++)
                    {
                        if( s[i][j]=='-' || s[i][j]=='|' )
                            putchar(S.X[++vars]>0 ? '|' : '-');
                        else
                            putchar(s[i][j]);
                    }
                    
                    putchar('\n');
                }
            }
        }
    }
}

/*

8

1 3
-.-

3 4
#.##
#--#
####

2 2
-.
#|

4 3
.|.
-//
.-.
#\/

3 3
/|\
\\/
./#

2 3
#|\
../

2 2
||
#.

3 3
|.\
##.
\./

*/
