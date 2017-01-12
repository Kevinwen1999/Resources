#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;
int M, N;
const int MAXN = 1000100;
int tail[MAXN];
vector <int> in2;
int leng = 0;
int main()
{
    scanf("%d", &M);
    int temp;
    for (int i = 0, a ; i < M; i++)
    {
        cin>>a;
        in2.push_back(a);
    }
    if (in2.size()==0)
    {
        cout<<0;
        return 0;
    }
    leng = 1;
    tail[0] = in2[0];
    for (int i = 1; i < in2.size(); i++)
    {
        if (in2[i] < tail[0])
            tail[0] = in2[i];
        else if (in2[i] > tail[leng-1])
            tail[leng++] = in2[i];
        else
        {
            int l = 0, r = leng - 1;
            while (l <= h)
            {
                int mid = l + (r-l) / 2;
                if (in2[tails[mid]] >= in2[i])
                    r = mid - 1;
                else
                    l = mid + 1;
            }
            tail[l] = in2[i];
        }
    }
    cout<<leng<<"\n";
}
