#include <bits/stdc++.h>
#define MAXN 410
using namespace std;
int R, C;
char grid[MAXN][MAXN];
struct Rect
{
    int c, h;
} rct[MAXN];
int height[MAXN];
int main()
{
    cin>>R>>C;
    for (int i = 0; i < R; i++)
    {
        cin>>grid[i];
    }
    int maxc = 0;
    for (int i = 0; i < R; i++)
    {
        int top = -1;
        for (int j = 0; j < C; j++)
        {
            if (grid[i][j] == 'X')
            {
                height[j] = 0;
                top = -1;
            }
            else
            {
                height[j]++;
                Rect r = (Rect){j, height[j]};
                if (top==-1) rct[++top] = r;
                else
                {
                    while(top>=0 && rct[top].h >= r.h)
                        r.c = rct[top--].c;
                    rct[++top] = r;
                }
                for (int k = 0; k <= top; k++)
                    maxc = max(maxc, 2*(rct[k].h + (j-rct[k].c+1)));
            }
        }
    }
    cout<<maxc-1<<"\n";
}

