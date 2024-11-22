#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>    // Para la función heurística
#include <climits>
#include <algorithm>
using namespace std;

// Estructura para representar un nodo
struct Node {
    int id;
    double g, h, f;
    Node* parent;
    Node(int id) : id(id), g(INT_MAX), h(0), f(INT_MAX), parent(nullptr) {}
};

// Heurística: distancia Manhattan
double heuristic(int current, int goal) {
    return abs(current - goal);
}

// A* mejorado
void AStar(vector<vector<pair<int, int>>>& grafo, int inicio, int objetivo) {
    int n = grafo.size();
    vector<Node*> nodos(n);

    for (int i = 0; i < n; ++i) {
        nodos[i] = new Node(i);
    }

    auto cmp = [](Node* a, Node* b) { return a->f < b->f; };
    set<Node*, decltype(cmp)> openList(cmp);  // Lista abierta como conjunto ordenado
    set<int> closedList;  // Lista cerrada como conjunto de IDs

    nodos[inicio]->g = 0;
    nodos[inicio]->h = heuristic(inicio, objetivo);
    nodos[inicio]->f = nodos[inicio]->g + nodos[inicio]->h;
    openList.insert(nodos[inicio]);

    while (!openList.empty()) {
        // Obtener el nodo con menor f
        Node* currentNode = *openList.begin();
        openList.erase(openList.begin());

        // Si llegamos al objetivo
        if (currentNode->id == objetivo) {
            cout << "Camino más corto de " << inicio << " a " << objetivo << " con costo: " << currentNode->g << endl;
            vector<int> path;
            while (currentNode != nullptr) {
                path.push_back(currentNode->id);
                currentNode = currentNode->parent;
            }
            reverse(path.begin(), path.end());
            for (int node : path) cout << node << " ";
            cout << endl;
            return;
        }

        closedList.insert(currentNode->id);

        // Explorar vecinos
        for (auto& vecino : grafo[currentNode->id]) {
            int vecinoId = vecino.first;
            int peso = vecino.second;

            // Si el vecino está en la lista cerrada, ignorar
            if (closedList.find(vecinoId) != closedList.end()) continue;

            double tentativeG = currentNode->g + peso;

            if (tentativeG < nodos[vecinoId]->g) {
                openList.erase(nodos[vecinoId]);  // Eliminar nodo con costos antiguos
                nodos[vecinoId]->g = tentativeG;
                nodos[vecinoId]->h = heuristic(vecinoId, objetivo);
                nodos[vecinoId]->f = nodos[vecinoId]->g + nodos[vecinoId]->h;
                nodos[vecinoId]->parent = currentNode;
                openList.insert(nodos[vecinoId]);  // Insertar nodo con costos actualizados
            }
        }
    }

    cout << "No se ha encontrado un camino." << endl;
}

int main() {
    vector<vector<pair<int, int>>> grafo(10);
    grafo[0].push_back({1, 1});
    grafo[0].push_back({2, 2});
    grafo[1].push_back({3, 1});
    grafo[2].push_back({3, 3});
    grafo[3].push_back({4, 1});
    grafo[4].push_back({5, 1});
    grafo[5].push_back({6, 2});
    grafo[6].push_back({7, 1});
    grafo[7].push_back({8, 1});
    grafo[8].push_back({9, 1});

    AStar(grafo, 0, 9);
    return 0;
}

