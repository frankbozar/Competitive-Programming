#include <stdio.h>
#include <vector>

using namespace std;

const int INF = 0x3FFFFFFF;


int main()
{
    int n;
    scanf("%d",&n);

    vector<int> p;

    for(int i = 0; i < n; i++)
    {
        int x;
        scanf("%d",&x);

        int l = lower_bound(p.begin(),p.end(),x)-p.begin();

        if( l == p.size() )
        {
            p.push_back(x);
        }
        else if( l == 0 )
        {
            vector<int> q;
            q.push_back(x);
            for(int i = 0; i < p.size(); i++)
               q.push_back(p[i]);
            swap(p,q);
        }
        else
        {
            p[l] = x;
        }
    }

    printf("%d\n",p.size());
    return 0;
}
