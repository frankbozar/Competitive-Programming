#include<cstdio>
#include<map>
#include<queue>
#include<vector>
using namespace std;

struct mat
{
    int n, m;
    vector<vector<int>> a;
    mat(int _n=0, int _m=0) : n(_n), m(_m), a(n, vector<int>(m)){}
    
    void read()
    {
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                scanf("%d", &a[i][j]);
    }
    
    mat flip() const
    {
        mat ret(n, m);
        ret.a.assign(a.rbegin(), a.rend());
        return ret;
    }
    
    mat rotate() const
    {
        mat ret(m, n);
        
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                ret.a[j][n-i-1]=a[i][j];
        
        return ret;
    }
    
    bool operator<(const mat& M) const
    {
        return a<M.a;
    }
    
    bool operator==(const mat& M) const
    {
        return a==M.a;
    }
};

int main()
{
    for(int n, m, p, q; scanf("%d%d%d%d", &n, &m, &p, &q) && (n||m||p||q); )
    {
        mat A(n, m), B(p, q);
        A.read();
        B.read();
        
        queue<mat> Q;
        map<mat, int> M;
        M[A]=0;
        
        for(Q.push(A); !Q.empty(); Q.pop())
        {
            A=Q.front();
            mat F=A.flip();
            mat R=A.rotate();
            
            if( M.find(F)==M.end() )
            {
                M[F]=M[A]+1;
                Q.push(F);
            }
            
            if( M.find(R)==M.end() )
            {
                M[R]=M[A]+1;
                Q.push(R);
            }
        }
        
        printf("%d\n", M.find(B)==M.end() ? -1 : M[B]);
    }
}

/*

4 6 6 4

1 2 3 3 2 1
0 0 1 0 1 -1
2 11 4 8 7 5
-3 -1 0 11 2 -8

1 -1 5 -8
2 1 7 2
3 0 8 11
3 1 4 0
2 0 11 -1
1 0 2 -3

3 2 2 3

0 1
1 2
2 0

2 1 0
1 2 0

0 0 0 0

*/
