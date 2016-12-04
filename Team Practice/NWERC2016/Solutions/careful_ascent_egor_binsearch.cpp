//performs binary search over the horizontal velocity
//         by simulating the flight for a given horizontal velocity


#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<double> vd;

int main(){
     
    int x,y;
    cin>>x>>y;
    int n;
    cin>>n;
     
    vi shield_lows(n);
    vi shield_ups(n);
    vd shield_fs(n);
    for(int i=0; i<n;i++)
       cin>> shield_lows[i] >> shield_ups[i] >> shield_fs[i];
    
    //sentinels:   
    shield_lows.push_back(y); shield_ups.push_back(y); shield_fs.push_back(1.0);
    double min_v=-10.0;
    double max_v=10.0;
    while(max_v-min_v>1e-9){
       double middle=(min_v+max_v)/2.0;
       double current_x=0.0;
       int last_y=0;
       for(int i=0;i<=n;i++){
            current_x+=(shield_lows[i]-last_y)*middle;
            current_x+=(shield_ups[i]-shield_lows[i])*shield_fs[i]*middle;
            last_y=shield_ups[i];
       }
       if (current_x>x)
            max_v=middle;
       else
            min_v=middle;
    }
    
    cout <<setprecision(12)<<  (max_v+min_v)/2.0<<"\n";
}


