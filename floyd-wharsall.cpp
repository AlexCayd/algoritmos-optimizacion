#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

const int INF = 1e9; 
const int N = 5;     // Número de nodos

int edges[N][N] = {
//    1      2      3      4      5
    {  0,     5,     7,   INF,   INF }, // 1 ->
    { INF,    0,     5,     7,   INF }, // 2 ->
    { INF,    6,     0,     6,   INF }, // 3 ->
    {  7,   INF,   INF,     0,     3 }, // 4 ->
    { INF,    7,     7,   INF,     0 }  // 5 ->
};

void printMatrix(const string& title,
                 const vector<vector<int>>& M,
                 bool isNext = false)
{
    cout << "\n  " << title << "\n";
    cout << "       ";
    for (int j = 0; j < N; j++)
        cout << setw(5) << (j + 1);
    cout << "\n    +";
    for (int j = 0; j < N; j++) cout << "-----";
    cout << "\n";

    for (int i = 0; i < N; i++) {
        cout << "    " << (i + 1) << " |";
        for (int j = 0; j < N; j++) {
            if (M[i][j] == INF)
                cout << setw(5) << "INF";
            else if (M[i][j] == -1)
                cout << setw(5) << " -";
            else
                cout << setw(5) << M[i][j];
        }
        cout << "\n";
    }
}

int main()
{
    // -- Inicializar matrices --
    vector<vector<int>> dist(N, vector<int>(N));
    vector<vector<int>> next(N, vector<int>(N, -1));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            dist[i][j] = edges[i][j];
            if (i != j && edges[i][j] != INF)
                next[i][j] = j + 1;   // guardamos nodo (1-based)
        }

    // -- Imprimir (k = 0) --
    cout << "+--------------------------------------+\n";
    cout << "|   FLOYD-WARSHALL  (estado inicial)   |\n";
    cout << "+--------------------------------------+\n";
    printMatrix("Matriz de distancias  D", dist);
    printMatrix("Matriz nodo siguiente M", next, true);

    // -- Iteraciones principales --
    for (int k = 0; k < N; k++) {
        cout << "\n+--------------------------------------+\n";
        cout << "|          Iteracion  k = " << (k + 1)
             << "             |\n";
        cout << "+--------------------------------------+\n";

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    int newDist = dist[i][k] + dist[k][j];
                    if (newDist < dist[i][j]) {
                        dist[i][j] = newDist;
                        next[i][j] = next[i][k];   // camino pasa por k
                    }
                }

        printMatrix("Matriz de distancias  D", dist);
        printMatrix("Matriz nodo siguiente M", next, true);
    }

    // ── Reconstrucción de caminos ─────────────
    cout << "\n+--------------------------------------+\n";
    cout << "|        CAMINOS MAS CORTOS            |\n";
    cout << "+--------------------------------------+\n";

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            cout << "  " << (i + 1) << " -> " << (j + 1) << "  |  costo = ";
            if (dist[i][j] == INF) {
                cout << "∞  |  sin camino\n";
                continue;
            }
            cout << setw(3) << dist[i][j] << "  |  ruta: ";
            int cur = i;
            cout << (cur + 1);
            while (cur != j) {
                cur = next[cur][j] - 1;
                cout << " -> " << (cur + 1);
            }
            cout << "\n";
        }

    return 0;
}