#include <bits/stdc++.h>
int main(){
  long long n,m=0; std::string a,b; std::cin>>n>>a>>b;
  for (int i=1; i<n; i++) a[i]^=(a[i-1]=='1'), b[i]^=(b[i-1]=='1');
  for (int i=0; i<n; i++) (m*=2)+=(a[i]-b[i]);
  std::cout<<std::abs(m)-1<<'\n';
}
