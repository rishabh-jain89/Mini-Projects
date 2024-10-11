#include <bits/stdc++.h>
using namespace std;

//Adjacency list representation of an Undirected graph

void addEdge(vector<vector<int>>& list, int e)
{
    for (int i = 0; i < e; i++)
    {
        int u, v;
        cout << "enter edge " << i + 1 << " :" ;
        cin >> u >> v;
        list[u].push_back(v);
        list[v].push_back(u);
    }
}

void print(vector<vector<int>> list)
{
    cout << "Adjacency list Representation:" << endl;
    for (int i = 0; i < list.size(); i++)
    {
        cout << i << "->";
        for (int j = 0; j < list[i].size(); j++)
        {
            cout << list[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int v;
    cout << "enter no of vertices you want to enter:";
    cin >> v;
    vector<vector<int>> adj_list(v);
    int e;
    cout << "enter no of edges you want to enter:" ;
    cin >> e;
    addEdge(adj_list, e);
    print(adj_list);
}