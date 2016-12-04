#include <iostream>
#include <cstdint>
#include <cstring>
using namespace std;

size_t const max_rows=40;
size_t const max_digits=400;

uint32_t const lots=0x7F7F7F7F;
static uint32_t dp[max_rows+1][max_rows+1][max_digits][11];
char digit[max_rows][max_digits+1];
char output[max_rows][max_digits+1];
int n,m;

uint32_t rec(int ra,int rb,int c,int sd,bool backtrack=false){
  if (backtrack) rec(ra,rb,c,sd,false);
  if (ra==rb or c==m) return 0;
  if (sd>9) return lots;

  uint32_t &res=dp[ra][rb][c][sd];
  if (res==lots or backtrack){
    uint32_t diff=0;
    for (int mid=ra; mid<=rb; mid++){
      uint32_t candidate=
        +diff
        +rec(ra,mid,c+1,0)
        +rec(mid,rb,c,sd+1);
      res=min(res,candidate);
      if (mid<rb){
        diff+=(digit[mid][c]!=sd);
      }
      if (backtrack and res==candidate){
        rec(ra,mid,c+1,0,true);
        rec(mid,rb,c,sd+1,true);
        while (mid-->ra) output[mid][c]=sd+'0';
        break;
      }
    }
  }
  return res;
}

int main(){
  cin>>n>>m;
  for (int i=0; i<n; i++) {cin>>digit[i]; for (auto &j: digit[i]) j-='0';}
  memset(dp,0x7F,sizeof dp);
  cerr<<"Cost: "<<rec(0,n,0,0,true)<<endl;
  for (int i=0; i<n; i++,cout<<'\n') for (int j=0; j<m; j++) cout<<(output[i][j]?output[i][j]:'?');
}
