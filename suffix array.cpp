#include <bits/stdc++.h>
#define MAXN 5001
using namespace std;
char T[MAXN]; //input string, up to 100K
int n;        //length of input string
int RA[MAXN], tempRA[MAXN]; //rank array and a temp rank array
int SA[MAXN], tempSA[MAXN]; //suffix array and a temp suffix array
int c[MAXN];                //for counting/radix sort
void cntsort(int k)
{
    int i, sum, maxi = max(300, n); //up to 255 ASCII character or length of n
    memset(c,0,sizeof c);
    for (i = 0; i < n; i++)
        c[i + k < n ? RA[i+k] : 0]++; //count the freq of each integer rank
    for (i = sum = 0; i < maxi; i++)
    {
        int t = c[i]; c[i] = sum; sum+=t;
    }
    for (i = 0 ; i < n; i++) //shuffle the suffix array
        tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
    for (i = 0 ; i < n; i++) //update suffix array
        SA[i] = tempSA[i];
}
void buildSA()
{
    int i, k, r;
    for (i = 0; i < n; i++) RA[i] = T[i];
    for (i = 0; i < n; i++) SA[i] = i; //initial SA and rankings
    for (k = 1; k < n; k <<= 1)
    {
        cntsort(k); // radix sort
        cntsort(0); // stable sort
        tempRA[SA[0]] = r = 0; //re ranking : starting from rank = 0
        // if same pair => same rank r; otherwise, increase r
        for (i = 1; i < n; i++)
            tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
        for (i = 0; i < n; i++)
            RA[i] = tempRA[i];
        if (RA[SA[n-1]] == n-1) break;
    }
}
int Phi[MAXN];
int PLCP[MAXN];
int LCP[MAXN];
void computeLCP()
{
    int i, L;
    Phi[SA[0]] = -1;
    for (i = 1; i < n; i++)
        Phi[SA[i]] = SA[i-1]; //which suffix is behind the current one
    for (i = L = 0; i < n; i++)
    {
        if (Phi[i] == -1) {PLCP[i] = 0; continue;}
        while (T[i+L] == T[Phi[i]+L]) L++; // L increase max n times
        PLCP[i] = L;
        L = max(L-1, 0); // L decrease max n times
    }
    for (i = 0; i < n; i++)
        LCP[i] = PLCP[SA[i]]; // put permuted LCP in order
}
int main()
{
    int b;
    scanf("%d ", &b);
    while (b--)
    {
        memset(T,0,sizeof T);
        n = (int)strlen(gets(T));
        T[n++] = '$';
        buildSA();
        computeLCP();
        //for (int i = 0; i < n; i++) printf("%2d\t%d\t%s\n", SA[i], LCP[i], T + SA[i]);
        int ans = n- SA[1];
        for (int i = 2; i < n; i++)
        {
            ans+=(n - 1 - SA[i]) - LCP[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}
