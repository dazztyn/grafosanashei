#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <stack>
#include <queue>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

void Dijkstra(vector<vector<pair<int,int>>> &grafo, int inicio, int objetivo)
{
    int n = grafo.size();
    vector <int> distancias(n, INT_MAX);
    distancias[inicio] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0,inicio});

    while(!pq.empty())
    {
        int distanciaActual = pq.top().first;
        int nodoActual = pq.top().second;
        pq.pop();

        if(objetivo == nodoActual)
        {
            cout << "distancia menor del nodo " << inicio << " a " << objetivo << ": " << distancias[objetivo] << endl;
            return;
        }

        if(distanciaActual > distancias [nodoActual]) continue;

        for(auto &[vecino, peso] : grafo[nodoActual])
        {
            int nuevaDistancia = distanciaActual + peso;

            if(nuevaDistancia < distancias[vecino])
            {
                distancias[vecino] = nuevaDistancia;
                pq.push({nuevaDistancia,vecino});
            }
        }
    }

    cout << "No se ha encontrado un camino" << endl;
}

void BFS(vector<vector<int>> grafo, int inicio)
{
    vector<bool> visitados(grafo.size(), false);
    queue<int> q;
    q.push(inicio);
    visitados[inicio] = true;

    while(!q.empty())
    {
        int nodo = q.front();
        q.pop();
        cout << nodo << " ";

        for(int vecino : grafo[nodo])
        {
            if(!visitados[vecino])
            {
                visitados[vecino] = true;
                q.push(vecino);
            }
        }
    }
    cout << endl;
}

void DFS(vector<vector<int>> grafo, int inicio)
{
    vector<bool> visitados(grafo.size(),false);
    stack<int> s;

    s.push(inicio);

    while(!s.empty())
    {
        int nodo = s.top();
        s.pop();

        if(!visitados[nodo])
        {
            visitados[nodo] = true;
            cout << nodo << " ";
        }

        for(int vecino : grafo[nodo])
        {
            if(!visitados[vecino])
            {
                s.push(vecino);
            }
        }
    }
    cout << endl;
}

int main()
{
    vector<vector<pair<int,int>>> grafo;

    /*
    grafo.push_back({{1, 4}, {2, 1}});
    grafo.push_back({{3, 1}});         
    grafo.push_back({{1, 2}, {3, 5}}); 
    grafo.push_back({});

    Dijkstra(grafo,2,1);
    */

    
    vector<vector<int>> grafo2;
    grafo2.push_back({1, 2});   // Nodo 0 conectado a 1 y 2
    grafo2.push_back({0, 3});   // Nodo 1 conectado a 0 y 3
    grafo2.push_back({0, 4});   // Nodo 2 conectado a 0 y 4
    grafo2.push_back({1});      // Nodo 3 conectado a 1
    grafo2.push_back({2});      // Nodo 4 conectado a 2

    //BFS(grafo2,3);

    //DFS(grafo2,0);
    
    return 0;
}