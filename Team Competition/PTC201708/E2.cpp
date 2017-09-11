#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
#include<cstring>
#include<string>
#include<map>
using namespace std;

typedef long long lld;

lld gcd(lld a, lld b)
{
    return b == 0 ? a : gcd(b, a%b);
}

struct Frac
{
    double u, d;
    Frac() { u = 0, d = 1; }
    
    Frac(lld x, lld y) : u((double)x/y), d(1.)
    {
    	
	}
	
    bool z() const
    {
        return u/d <= 1e-6;
    }
    
    Frac nor(const Frac &l) const
    {
        Frac res = l;
        res.u = res.u/res.d;
        res.d = 1.;
        return res;
    }
    
    Frac operator/(const Frac &r) const
    {
        if (r.z())
            exit(0);
        Frac res;
        res.u = u * r.d;
        res.d = d*r.u;
        res = nor(res);
        return res;
    }
    
    Frac operator-(const Frac &r) const
    {
        Frac res;
        res.u = u*r.d - r.u*d;
        res.d = d*r.d;
        res = nor(res);
        return res;
    }
    
    Frac operator*(const Frac &r) const
    {
        Frac res;
        res.u = u* r.u;
        res.d = d*r.d;
        res = nor(res);
        return res;
    }
    
    void print()
    {
        printf("%.2f\n", u/d);
    }
};

int main()
{
	int T;
	scanf("%d", &T);
	
	for(int t = 0; t < T; t++)
	{
		lld h, w, x1, y1, x2, y2;
		scanf("%lld %lld", &h, &w);
		scanf("%lld %lld", &x1, &y1);
		scanf("%lld %lld", &x2, &y2);
		
		x1--;
		x2--;
		y1--;
		y2--;
		
		int n = h*w, m = h*w;
		vector<vector<Frac>> v(m, vector<Frac>(n + 1));
		
		for(int i = 0; i < h; i++)
			for(int j = 0; j < w; j++)
			{
				if( i == x2 && j == y2 )
				{
					v[i*w+j][i*w+j] = Frac(1, 1);
					v[i*w+j][n] = Frac(0, 1);
					continue;
				}
				
				int deg = 0;
				
				if( i != 0 )
				{
					v[i*w+j][(i-1)*w+j] = Frac(-1, 1);
					deg++;
				}
				
				if( i != h-1 )
				{
					v[i*w+j][(i+1)*w+j] = Frac(-1, 1);
					deg++;
				}
				
				if( j != 0 )
				{
					v[i*w+j][i*w+(j-1)] = Frac(-1, 1);
					deg++;
				}
				
				if( j != w-1 )
				{
					v[i*w+j][i*w+(j+1)] = Frac(-1, 1);
					deg++;
				}
				
				v[i*w+j][i*w+j] =Frac(deg, 1);
				v[i*w+j][n] = Frac(deg, 1);
			}
		/*	
		for(int i = 0; i < m; i++)
		{
			for(int j = 0; j <= n; j++)
				printf("%lld/%lld ", v[i][j].u, v[i][j].d);
			puts("");
		}
		*/	
			
			
		int rank = 0;
        for (int i = 0; i < n && rank < m; i++)
        {
            for (int j = rank; j < m; j++)
                if (!v[j][i].z())
                    swap(v[rank], v[j]);
            if (v[rank][i].z())
                continue;
            for (int j = rank + 1; j < m; j++)
                for (int k = n; k >= i; k--)
                    v[j][k] = v[j][k] - v[j][i] / v[rank][i] * v[rank][k];
            rank++;
        }
        
        vector<Frac> ans(n);
        for (int i = n - 1; i >= 0; i--)
        {
            ans[i] = v[i][n] / v[i][i];
            for (int j = i - 1; j >= 0; j--)
            {
                v[j][n] = v[j][n] - v[j][i] * ans[i];
                v[j][i].u = 0;
            }
        }
        
        if( x1 == x2 && y1 == y2 )
        {
        	double xxx = 0;
        	int deg = 0;
        	
        	if( x1 != 0 )
        	{
        		xxx += ans[(x1-1)*w+y1].u/ans[(x1-1)*w+y1].d;
        		deg++;
			}
        		
			if( x1 != h-1 )
        		xxx += ans[(x1+1)*w+y1].u/ans[(x1+1)*w+y1].d,deg++;;
        	if( y1 != 0 )
        		xxx += ans[x1*w+(y1-1)].u/ans[x1*w+(y1-1)].d,deg++;;
        	if( y1 != w-1 )
        		xxx += ans[x1*w+(y1+1)].u/ans[x1*w+(y1+1)].d,deg++;;
        		
        	printf("%.2f\n", xxx/deg+1);
		}
        else
        	ans[x1*w+y1].print();
        /*
        for (int i = 0; i < n; i++)
        {
            printf("x[%d] = ", i + 1);
            ans[i].print();
            printf("\n");
        }
        */
		
	}
	/*
    int init=1;
    for (int pro; scanf("%d", &pro) && pro != 0; )
    {
        init ? init=0 : printf("\n");
        int n, m;
        scanf("%d%d", &n, &m);
        vector<vector<Frac>> v(m, vector<Frac>(n + 1));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n + 1; j++)
                v[i][j].read();
        int rank = 0;
        for (int i = 0; i < n && rank < m; i++)
        {
            for (int j = rank; j < m; j++)
                if (!v[j][i].z())
                    swap(v[rank], v[j]);
            if (v[rank][i].z())
                continue;
            for (int j = rank + 1; j < m; j++)
                for (int k = n; k >= i; k--)
                    v[j][k] = v[j][k] - v[j][i] / v[rank][i] * v[rank][k];
            rank++;
        }
        printf("Solution for Matrix System # %d\n", pro);
        bool valid = true;
        for (int i = rank; i < m; i++)
            if (!v[i][n].z())
                valid = false;
        if (!valid)
        {
            printf("No Solution.\n");
            continue;
        }
        if (rank != n)
        {
            printf("Infinitely many solutions containing %d arbitrary constants.\n", n - rank);
            continue;
        }
        vector<Frac> ans(n);
        for (int i = n - 1; i >= 0; i--)
        {
            ans[i] = v[i][n] / v[i][i];
            for (int j = i - 1; j >= 0; j--)
            {
                v[j][n] = v[j][n] - v[j][i] * ans[i];
                v[j][i].u = 0;
            }
        }
        for (int i = 0; i < n; i++)
        {
            printf("x[%d] = ", i + 1);
            ans[i].print();
            printf("\n");
        }
    }
	*/
}

/*
 
5
2 2
1 2
2 1
1 2
1 1
1 2
1 3
1 2
1 1
3 3
2 2
1 1
2 2
1 1
1 1
 */
