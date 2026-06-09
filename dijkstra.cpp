#include <iostream>

using namespace std;

// Definición de infinito solicitada
double inf = 1.0 / 0.0;

// Número de vértices en el grafo
#define N 6

// Función arg_min
int arg_min(double T[], bool S[]) {
    int amin = -1;
    double m = inf;
    for (int i = 0; i < N; ++i) {
        if (T[i] < m && !S[i]) {
            m = T[i];
            amin = i;
        }
    }
    return amin;
}

int main() {
    // Declaraciones de variables
    int start = 1; // Del nodo 1 al 6
    int target = 6; // 
    int v;

    // Arreglos
    double T[N];
    int M[N];
    bool S[N];
    int Q[N]; // Cola (no utilizada)

    // Inicialización de arreglos
    for(int i=0; i<N; i++) T[i] = inf;
    for(int i=0; i<N; i++) M[i] = 0;
    for(int i=0; i<N; i++) S[i] = false;

    // DEFINICIÓN DE LA MATRIZ D
    // Se coloca aquí para que esté disponible en todo el main
    double D[N][N] = {
        {0,   3,     1,   3, inf, inf},
        {3,   0,     4, inf, inf, inf},
        {1,   4,     0, inf,   7,   5},
        {3,   inf, inf,   0, inf,   2},
        {inf, inf,   7, inf,   0,   4},
        {inf, inf,   5,   2,   4,   0}
    };

    start -= 1;
    target -= 1;

    v = start;
    S[v] = true;
    T[v] = 0;

    while (v != -1) {
        for (int j = 0; j < N; ++j) {
            if (!S[j]) {
                double w = T[v] + D[v][j]; // Ahora D está definido
                if (w < T[j]) {
                    T[j] = w;
                    M[j] = v;
                }
            }
        }

        v = arg_min(T, S);
        if (v >= 0) {
            S[v] = true;
        }
    }

    // Reconstrucción del camino
    int pIndex = 0;
    int P[N];
    P[pIndex++] = target;

    while (target != start) {
        target = M[P[pIndex - 1]];
        P[pIndex++] = target;
    }

    // Marcamos el nodo de origen (raíz) con -1
    M[start] = -1;

    cout << "Árbol desde el nodo: " << start + 1 << endl;
    cout << "Distancia\tnodos";

    for (int i = N - 1; i >= 0; --i) { 
        int p = i;
        cout << "\n" << T[i] << "\t\t";
        while (p != -1) {
            cout << "<=" << p + 1;
            p = M[p];
        }
    }
    cout << endl;

    return 0;
}