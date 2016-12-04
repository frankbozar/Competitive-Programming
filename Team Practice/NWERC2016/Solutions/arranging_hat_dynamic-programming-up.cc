#include <iostream>
#include <cstring>
#include <cstdint>
using namespace std;

constexpr uint16_t lots=10000;

constexpr size_t max_rows=40;
constexpr size_t max_digits=400;

static pair<uint16_t,uint16_t> dp[max_rows+2][max_rows+2][max_digits+2][11];
static char digit[max_rows][max_digits+1];
static char output[max_rows][max_digits+1];
int n,m;

void rec(int ra,int rb,int c,int sd){
  if (ra==rb or c==m) return;
  auto r=dp[ra][rb][c][sd].second;
  rec(ra,r,c+1,0);
  rec(r,rb,c,sd+1);
  for (int x=r; x-->ra;) output[x][c]=sd+'0';
}

int main(){
  cin>>n>>m;
  for (int i=0; i<n; i++) {cin>>digit[i]; for (auto &j: digit[i]) j-='0';}
  memset(dp,0x70,sizeof dp);
  for (int diff=0; diff<=n; diff++){
    for (int ra=0,rb=diff; rb<=n; ra++,rb++){
      for (int c=m; c>=0; --c){
        for (char sd=10; sd--;){
          auto &res=dp[ra][rb][c][sd];
          if (ra==rb or c==m) {res={0,rb};continue;}

          uint16_t diff=0;
          for (int mid=ra; mid<=rb; mid++){
            uint16_t candidate=
              +diff
              +(ra<mid? dp[ra][mid][c+1][0].first: 0)
              +(mid<rb? dp[mid][rb][c][sd+1].first: 0);
            res=min(res,{candidate,mid});
            if (mid<rb){
              diff+=(digit[mid][c]!=sd);
            }
          }
        }
      }
    }
  }
  rec(0,n,0,0);
  for (int i=0; i<n; i++,cout<<'\n') for (int j=0; j<m; j++) cout<<(output[i][j]?output[i][j]:'?');
}
