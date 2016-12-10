#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void checktopo(int cur)
{
    if (temp[cur]){flag = false; return;} // no topo order
    if (per[cur]) return;
    temp[cur] = true;
    for (int i = 0; i < (int)adj[cur].size(); i++)
    {
        checktopo(adj[cur][i]);
    }
    temp[cur] = false;
    per[cur] = true;
    //push cur to vector
    //don't forget to reverse
}

int adj[10][10];
int V = 7;

vector<int> topological_sort()
{
	vector<int> result;
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
        visited[i] = false;
	while (true)
    {
		bool allVisited = true;
		for (int i = 0; i < V; i++)
            allVisited = allVisited & visited[i];
		if (allVisited) return result;
		vector<int> inDegree;
		for (int i = 0; i < V; i++)
        {
			if (!visited[i])
			{
				int indeg = 0;
				for (int j = 0; j < V; j++)
					if (!visited[j] && adj[j][i])
                        indeg += 1;
				if (indeg == 0) inDegree.push_back(i);
			}
		}
		sort(inDegree.begin(), inDegree.end());
		if (inDegree.empty())
        {
			vector<int> e;
			return e;
		}
		for (int i = 0; i <= 0; i++)
        {
			int cur = inDegree[i];
			visited[cur] = true;
			for (int j = 0; j < V; j++)
            {
				adj[cur][j] = 0;
				adj[j][cur] = 0;
			}
			result.push_back(cur);
		}
	}
}

int main()
{
    cin>>V;
	while(1)
    {
		int a, b;
		cin >> a >> b;
        adj[a][b] = 1;
	}
	vector<int> result = topological_sort();
	if (result.empty())
    {
        cout<<"NO TOPO ORDER"<<endl;
        return 0;
    }
	for (int n = 0; n < result.size(); n++)
		cout << result[n] <<" ";
}
