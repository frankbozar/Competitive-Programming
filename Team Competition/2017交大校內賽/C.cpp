#include <stdio.h>
#include <cmath>
#include <algorithm>

using namespace std;

const double EPS = 1e-7;
const double SQ2 = sqrt(2);

int main()
{
    int T;
    scanf("%d", &T);

    for(int t = 0; t < T; t++)
    {
        int wa,ha,wb,hb;
        scanf("%d %d %d %d", &wa, &ha, &wb, &hb);

        if( ha > wa )
            swap(wa, ha);

        if( hb > wb )
            swap(wb, hb);

        int aa, ab;

        aa = wa*ha;
        ab = wb*hb;

        if( aa == ab )
        {
            if( wa == wb && ha == hb )
                puts("YY");
            else
                puts("NN");
        }
        else
        {
            bool sw = false;

            if( aa < ab )
            {
                swap(wa, wb);
                swap(ha, hb);
                sw = true;
            }

            if( wa >= wb && ha >= hb )
            {
                if( sw )
                    puts("NY");
                else
                    puts("YN");
            }
            else
            {
                double A=wb*wb+ha*ha;
                double B=-2*pow(hb, 2)*ha;
                double C=pow(ha, 2)*pow(hb, 2)-pow(wb, 2)*pow(hb, 2);
                double D=sqrt(B*B-4*A*C);
                double ans=(-B+D)/(2*A);

                double y=ans;
                double x=(hb*(ha-y))/wb;
                double t=x+y/x*(ha-y);

                ans=(-B-D)/(2*A);
                y=ans;
                x=(hb*(ha-y))/wb;
                double tt=x+y/x*(ha-y);

                if( t<=ha || x>=0 && y>=0 && tt<=ha )
                    puts(sw ? "NY" : "YN");
                else
                    puts("NN");

                /*
                if( hb*hb <= ha*ha+ha*ha && wb*wb <= (wa-hb/SQ2)*(wa-hb/SQ2) + (ha-hb/SQ2)*(ha-hb/SQ2) - EPS )
                {
                    if( sw )
                        puts("NY");
                    else
                        puts("YN");
                }
                else
                    puts("NN");*/
            }
        }
    }

    return 0;
}
/*
2
1 1 1 1
1 2 1 1

*/
