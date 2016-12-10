#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
vector < pair <int, int> >adjacencyList[1050];
long dist[1500]; // shortest path to node
bool done[1500]; // flag to indicate if current node is in queue
queue <int> buff;
int V; // total number of nodes
int E; // total number of edges
// Too lazy to code negatice cycle, if any node entered the queue (buff) for more that V times than negative cycle exist
void spfa( int st);
int main()
{
    cin>>V;
    cin>>E;
    for (int i = 0; i <= V; i++)
    {
        dist[i] = 999999999;
        done[i] = false;
    }
    for (int j = 1; j <=E ; j++)
    {
        int a, b, c;
        cin>>a>>b>>c; //a: from, b: to, c: weight of edge
        adjacencyList[a].push_back(make_pair(b,c));
        adjacencyList[b].push_back(make_pair(a,c));
    }
    spfa(1); // SPFA from sourse
    for (int i = 1; i <= V; i++)
    {
        if (dist[i]==999999999) cout<<-1<<"\n"; // unreachable
        else cout<<dist[i]<<"\n";
    }
    return 0;
}
void spfa(int st) // st: starting node
{
    dist[st] = 0; // dist to source is 0
    buff.push(st); // push node to queue
    done[st] = true; // current node is in the queue
    while (!buff.empty())
    {
        int temp = buff.front(); //current top of buffer
        buff.pop(); // pop
        done[temp] = false; //current node no longer in queue
        for (int i = 0; i < (int)adjacencyList[temp].size(); i++) //for each node that is connected to the current node
        {
            pair<int,int> v = adjacencyList[temp][i];
            if ((dist[temp]+ v.second) < dist[v.first]) //shorter path exist
            {
                dist[v.first] = dist[temp]+v.second; // update shortest path
                if (done[v.first]==false) // if next node not in queue, push it in queue
                {
                    buff.push(v.first);
                    done[v.first] = true;
                }
            }
        }

    }
}
