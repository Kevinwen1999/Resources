#include <iostream>
#include <cstring>
using namespace std;
int M, N;
int in1[1010],in2[1010];
int dp[1010][1010];
int LCS(int m, int n)
{
    if (m==-1||n==-1) return 0;
    if (dp[m][n]!=-1) return dp[m][n];
    if (in1[m]==in2[n]) return dp[m][n] = 1+ LCS(m-1,n-1);
    return dp[m][n] = max(LCS(m,n-1),LCS(m-1,n));
}
int main()
{
    cin>>M>>N;
    for (int i = 0 ; i < M; i++)
        cin>>in1[i];
    for (int i = 0 ; i < N; i++)
        cin>>in2[i];
    memset(dp,-1,sizeof dp);
    cout<<LCS(M-1,N-1)<<endl;
}
