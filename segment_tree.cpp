#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
const int MAXN = 4000
int node[MAXN];
int lazy[MAXN];
using namespace std;
int getSegmentTreeSize(int N)
{
    int size = 1;
    for (; size < N; size <<= 1);
    return size << 1;
}
void buildtree(int stidx, int L, int R)
{
    if (L==R)
    {
        //assign value to node[stidx];
        return;
    }
    int le = 2 * stidx, ri = le + 1, mid = (L + R) / 2;
    buildtree(le, L, mid);
    buildtree(ri, mid+1, R);
    int p1 = node[le], p2 = node[ri];
    //assign value to node[stidx];
}
//call query(1,0,N-1,i,j);
int query(int stidx, int L, int R, int i, int j) // i and j are the given range
{
    if (i > R || j < L) return -1; //out of range
    if (L >= i && R <= j) return node[stidx];
    int p1 = query(2*stidx, L, (L+R)/2, i,j);
    int p2 = query(2*stidx + 1, (L+R)/2 + 1, R, i,j);
    if (p1==-1) return p2;
    if (p2==-1) return p1;
    return //base on  the calculation, same as in buildtree;
}
//call update(1,0,N-1, index_of_value, value);
void update(int stidx, int L, int R, int idx, int val)
{
    if (L==R)
    {
        //assign val to node[stidx];
        return;
    }
    int le = 2 * stidx, ri = le + 1, mid = (L + R) / 2;
    if (idx <= mid)
        update(le, L, mid, idx, val);
    else
        update(ri, mid+1, R, idx, val);
    int p1 = node[le], p2 = node[ri];
    //node[stidx] = merge result like in previous using node[le] and node[ri];
}
// range update with lazy propagation
// ql and qr define the update range
void rangeupdate(int stidx, int L, int R, int ql, int qr, int val)
{
    if (lazy[stidx]!=0) // need updating
    {
        //update current segment as everything is within range
        node[stidx] += (R-L+1) * lazy[stidx]; // if solving RMQ and alike don't multiply (R-L+1)
        //if it is not a leaf node, we need to update lazy value for the children
        if (L!=R)
        {
            lazy[stidx*2] += lazy[stidx];
            lazy[stidx*2+1] += lazy[stidx];
        }
        //finish updating for current idx
        lazy[stidx] = 0;
    }
    //out of range
    if (L>R || L > qr || R < ql)
        return;
    //Current segment is fully in update range. Use lazy propagation
    if (L >= ql && R <= qr)
    {
        node[stidx] += (R-L + 1) * val;
        //if it is not a leaf node, we need to update lazy value for the children
        if (L!=R)
        {
            lazy[stidx*2] += val;
            lazy[stidx*2+1] += val;
        }
        return;
    }
    //if not, recur for children and use result to update
    int mid = (L+R)/2;
    rangeupdate(stidx*2,L,mid,ql,qr,val);
    rangeupdate(stidx*2+1,mid+1,R,ql,qr,val);
    node[stidx] = node[stidx*2] + node[stidx*2+1];
}
// use this when using lazy propagation
int rangequery(int stidx, int L, int R, int ql, int qr)
{
    if (lazy[stidx]!=0) // need updating
    {
        //update current segment as everything is within range
        node[stidx] += (R-L+1) * lazy[stidx];
        //if it is not a leaf node, we need to update lazy value for the children
        if (L!=R)
        {
            lazy[stidx*2] += lazy[stidx];
            lazy[stidx*2+1] += lazy[stidx];
        }
        //finish updating for current idx
        lazy[stidx] = 0;
    }
    //out of range
    if (L>R || L > qr || R < ql)
        return 0;
    //Complete in range
    if (L >= ql && R <= qr)
        return node[stidx];
    //else do it the old way
    int mid = (L+R)/2;
    return rangequery(stidx*2,L,mid,ql,qr) + rangequery(stidx*2+1,mid+1,R,ql,qr);
}
int main()
{

}
