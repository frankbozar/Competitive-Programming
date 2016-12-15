#include <stdio.h>
#include <vector>
#include<algorithm>

using namespace std;

typedef long long lld;

lld ans;

struct SAT
{
    int n,m,rem,level, tcnt=0;
    vector<vector<int> > C,CNT;
    vector<int> X, STAT;
    vector<vector<vector<int>>> POS;
    vector<vector<int>> I;
    vector<int> UNIT;
    vector<vector<int>> ORDER;

    SAT(int _n, vector<vector<int>>& cnf) : n(_n), level(0), C(cnf), I(1)
    {
        m = C.size();
        rem = n;

        for(vector<int> &c : C)
            CNT.push_back({0,0,(int)c.size()});

        X.resize(n+1);
        STAT.assign(n+1,0);
        POS.assign(n+1,{{},{}});

        for(int i = 0; i < m; i++)
            for(int x : C[i])
                POS[abs(x)][x < 0 ? 0 : 1].push_back(i);

        for(vector<int> &c : C)
            if( c.size() == 1 )
                UNIT.push_back(c[0]);

        for(int i = 1; i <= n; i++)
            ORDER.push_back({(int)(POS[i][0].size()+POS[i][1].size()),i});

        sort(ORDER.rbegin(),ORDER.rend());
    }


    bool assign(int x, int val, int stat)
    {
        ////printf("ass\n");
        rem--;
        X[x] = val;
        STAT[x] = stat;
        bool res = true;

        for(int i = 0; i < 2; i++)
            for(int c : POS[x][i])
            {
                int t=CNT[c][1];
                CNT[c][2]--;
                CNT[c][val==i]++;
                if(CNT[c][1]==1 && t==0)
                    tcnt++;

                if( CNT[c][2] == 1 && CNT[c][1] == 0 )
                    for(int y : C[c])
                        if( STAT[abs(y)] == 0 )
                        {
                            UNIT.push_back(y);
                            break;
                        }
                res &= !(CNT[c][1] == 0 && CNT[c][2] == 0);
            }
        return res;
    }

    void unassign(int x)
    {
        //printf("unass\n");
        rem++;
        STAT[x]=0;

        for(int i = 0; i < 2; i++)
            for(int c : POS[x][i])
            {
                int t=CNT[c][1];
                CNT[c][2]++;
                CNT[c][X[x]==i]--;
                if(CNT[c][1]==0 && t==1)
                    tcnt--;
            }
    }

    bool imply()
    {
        //printf("imp\n");
        while( !UNIT.empty() )
        {
            int x = UNIT.back();
            int val = x > 0;
            //printf("~x=%d\n");
            UNIT.pop_back();

            if( STAT[abs(x)] != 0 && X[abs(x)] == val)
                continue;
            if( STAT[abs(x)] != 0 && X[abs(x)] != val )
                return false;

            I.back().push_back(abs(x));
            if( !assign(abs(x),val,2) )
                return false;
        }
        //printf("~imp\n");
        return true;
    }

    void unimply()
    {
        //printf("unimp\n");
        for(int x : I.back())
            unassign(x);
        I.back().clear();
    }

    bool sol()
    {
        //printf("rem=%d n=%d m=%d %d %d\n", rem, n, m, ORDER.size(), STAT.size());
        if( !imply() )
            return false;
        if( tcnt==C.size() )
        {
            //for(int i=1; i<=n; i++)
                //printf("x=%d stat=%d X=%d\n", i, STAT[i], X[i]);
            ans+=(1LL)<<(rem);
            return false;
        }
        int x;
        for(int i = 0; STAT[ x=ORDER[i][1] ]; i++)
            ;//printf("!!!%d %d\n", i, x);
        level++;
        I.push_back({});
        if(assign(x,rand()&1,1))
            sol();

        unassign(x);
        unimply();
        UNIT.clear();

        if(assign(x,X[x]^1,1))
            sol();

        unassign(x);
        unimply();
        level--;
        I.pop_back();

        return false;
    }
};



int main()
{
    int T;
    scanf("%d", &T);
    for(; T>0; T--)
    {
        int n, m;
        vector<vector<int>> cnf;
        scanf("%d%d", &n, &m);
        for(int i=0; i<m; i++)
        {
            cnf.push_back({});
            for(int x; scanf("%d", &x) && x;)
                cnf.back().push_back(x);
        }
        SAT sat(n, cnf);
        ans=0;
        sat.sol();
        printf("%lld\n", ans);
    }





    return 0;
}


/*

3
2 4
1 2 0
1 -2 0
-1 2 0
-1 -2 0
3 2
3 1 2 0
-1 -2 -3 0
33 1
4 0


*/
