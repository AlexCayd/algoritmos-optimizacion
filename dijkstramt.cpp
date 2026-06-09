#include <bits/stdc++.h>
using namespace std;

int main() {
    const int NUM_NODOS = 5;
    const int INFINITO = 1e9;

    vector<pair<int,int>> listaAdyacencia[NUM_NODOS+1];

    // Asignar los pesos 
    listaAdyacencia[1].push_back({2,5}); // De 1 a 2 hay distancia de 5
    listaAdyacencia[1].push_back({3,7}); // De 1 a 3 hay distancia de 7
    listaAdyacencia[2].push_back({3,5}); // De 2 a 3 hay distancia de 5
    listaAdyacencia[2].push_back({4,7}); // De 2 a 4 hay distancia de 7
    listaAdyacencia[3].push_back({2,6}); // De 3 a 2 hay distancia de 6
    listaAdyacencia[3].push_back({4,6}); // De 3 a 4 hay distancia de 6
    listaAdyacencia[4].push_back({1,7}); // De 4 a 1 hay distancia de 7
    listaAdyacencia[4].push_back({5,3}); // De 4 a 5 hay distancia de 3
    listaAdyacencia[5].push_back({2,7}); // De 5 a 2 hay distancia de 7
    listaAdyacencia[5].push_back({3,7}); // De 5 a 3 hay distancia de 7

    int origen = 5;
    int destino = 4; 

    vector<int> distancia(NUM_NODOS+1, INFINITO);
    vector<int> anterior(NUM_NODOS+1, -1);
    vector<bool> visitado(NUM_NODOS+1, false);

    distancia[origen] = 0;

    int iteraciones = 0;

    for (int i = 1; i <= NUM_NODOS; ++i) {
        int nodoActual = -1;
        int mejorDistancia = INFINITO;

        // Buscar el nodo no visitado con menor distancia
        for (int v = 1; v <= NUM_NODOS; ++v) {
            if (!visitado[v] && distancia[v] < mejorDistancia) {
                mejorDistancia = distancia[v];
                nodoActual = v;
            }
        }

        if (nodoActual == -1) break;

        visitado[nodoActual] = true;
        iteraciones++;

        if (nodoActual == destino) break;

        // Mejorar las distancias si se puede
        for (int i = 0; i < listaAdyacencia[nodoActual].size(); i++) {

        int vecino = listaAdyacencia[nodoActual][i].first;
        int peso    = listaAdyacencia[nodoActual][i].second;

        if (!visitado[vecino] &&
            distancia[nodoActual] + peso < distancia[vecino]) {

            distancia[vecino] = distancia[nodoActual] + peso;
            anterior[vecino] = nodoActual;
        }
    }
    }

    // Reconstrucción de la ruta
    vector<int> ruta;
    for (int v = destino; v != -1; v = anterior[v])
        ruta.push_back(v);

    reverse(ruta.begin(), ruta.end());

    // Imprimir resultados
    cout << "Ruta mas corta de " << origen 
         << " a " << destino << ": ";

    for (size_t i = 0; i < ruta.size(); ++i) {
        cout << ruta[i] 
             << (i + 1 < ruta.size() ? " -> " : "\n");
    }

    cout << "Distancia total: " 
         << distancia[destino] << "\n";

    cout << "Iteraciones realizadas hasta extraer el destino: " 
         << iteraciones << "\n";

    return 0;
}