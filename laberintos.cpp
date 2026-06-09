#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Codificacion: 0=libre, 1=pared, 8=inicio, 9=fin
const int FILAS = 5;
const int COLS  = 8;

const int datos[FILAS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 9},
    {1, 0, 1, 0, 1, 0, 1, 1},
    {8, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

struct Celda { int fila, col; };

vector<vector<int>>  laberinto;
vector<vector<bool>> visitado;
vector<Celda> camino;
vector<Celda> solucion;

// Deltas para moverse en 4 direcciones: arriba, abajo, izquierda, derecha
const int dFila[] = {-1, 1,  0, 0};
const int dCol[]  = { 0, 0, -1, 1};

void imprimirLaberinto(const vector<Celda>& sol) {
    vector<vector<bool>> enCamino(FILAS, vector<bool>(COLS, false));
    for (const auto& c : sol)
        enCamino[c.fila][c.col] = true;

    cout << "(# = pared, . = libre, * = camino, I = inicio, S = salida)\n\n";
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLS; j++) {
            char ch;
            if      (laberinto[i][j] == 8) ch = 'I';
            else if (laberinto[i][j] == 9) ch = 'S';
            else if (laberinto[i][j] == 1) ch = '#';
            else if (enCamino[i][j])        ch = '*';
            else                            ch = '.';
            cout << ch << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

bool esValida(int f, int c) {
    if (f < 0 || f >= FILAS || c < 0 || c >= COLS) return false;
    if (laberinto[f][c] == 1) return false; // pared
    if (visitado[f][c])       return false; // ya visitada
    return true;
}

bool resolver(int f, int c) {
    visitado[f][c] = true;
    camino.push_back({f, c});

    if (laberinto[f][c] == 9) { // llegamos al destino
        solucion = camino;
        return true;
    }

    for (int d = 0; d < 4; d++) {
        int nf = f + dFila[d];
        int nc = c + dCol[d];
        if (esValida(nf, nc) && resolver(nf, nc))
            return true;
    }

    // Backtrack: esta celda no lleva a la solucion
    camino.pop_back();
    visitado[f][c] = false;
    return false;
}

int main() {
    // Cargar el laberinto desde la variable fija
    laberinto.assign(FILAS, vector<int>(COLS));
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLS; j++)
            laberinto[i][j] = datos[i][j];

    // Localizar inicio (8) y fin (9) en la matriz
    Celda inicio = {-1,-1}, fin = {-1,-1};
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLS; j++) {
            if (laberinto[i][j] == 8) inicio = {i, j};
            if (laberinto[i][j] == 9) fin    = {i, j};
        }

    if (inicio.fila == -1 || fin.fila == -1) {
        cerr << "Error: falta inicio (8) o fin (9) en el laberinto.\n";
        return 1;
    }

    cout << "Laberinto " << FILAS << "x" << COLS << "\n";
    cout << "Inicio: (" << inicio.fila+1 << "," << inicio.col+1 << ")  "
         << "Fin: ("    << fin.fila+1    << "," << fin.col+1    << ")\n\n";
    imprimirLaberinto({});

    visitado.assign(FILAS, vector<bool>(COLS, false));

    if (!resolver(inicio.fila, inicio.col)) {
        cout << "No existe camino hacia la salida.\n";
        return 0;
    }

    cout << "Solucion (" << solucion.size() << " pasos):\n";
    for (size_t k = 0; k < solucion.size(); k++)
        cout << "  Paso " << setw(3) << k+1
             << ": (" << solucion[k].fila+1 << "," << solucion[k].col+1 << ")\n";

    cout << '\n';
    imprimirLaberinto(solucion);
    return 0;
}