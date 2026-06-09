#include <iostream> //cin, cout
#include <stdlib.h> //srand, rand
#include <time.h>   //srand, rand

using namespace std;

//**********************************************************
// # Giapetto's problem
//
// # This finds the optimal solution for maximizing Giapetto's profit
//
//   /* Decision variables */
//  var x1 >=0;  /* soldier */
//  var x2 >=0;  /* train */
//  var x3 >=0;  /* nutty */
//
//     /* Objective function */
//  maximize z: 3*x1 + 2*x2 + 4*x3;
//
//   /* Constraints */
//  s.t. Finishing : 2*x1 + x2  + 3*x3   <= 99;
//  s.t. Carpentry : x1  + x2   + 0.5*x3 <= 79;
//  s.t. Demand    : x1 <= 40;
//
//************************************************************

// Cromosomas: 3 variables x1, x2, x3, cada una codificada en 1 byte (8 bits)
const int C = 24;   // 3 bytes = 24 bits por individuo
const int M = 200;  // Numero de individuos (poblacion)
const int G = 200;  // Numero de generaciones

bool individuo[M][C]; // M individuos con C cromosomas c/u

// -----------------------------------------------------------
// Convierte bits del cromosoma [from..to] a entero sin signo
// -----------------------------------------------------------
unsigned int ctoInt(bool *cromosoma, int from, int to) {
    unsigned int r = 0;
    for (int i = 0, j = from; j <= to; i++, j++)
        r = r + (cromosoma[j] << i);
    return r;
}

// -----------------------------------------------------------
// Evalua que tan bueno es un individuo segun la funcion obj.
// Devuelve valor negativo si viola alguna restriccion.
// -----------------------------------------------------------
int fitness(bool *cromosoma) {
    // variable x1: bits  0..7  (soldier)
    // variable x2: bits  8..15 (train)
    // variable x3: bits 16..23 (nutty)

    unsigned int x1 = ctoInt(cromosoma, 0,  7);
    unsigned int x2 = ctoInt(cromosoma, 8,  15);
    unsigned int x3 = ctoInt(cromosoma, 16, 23);

    // Restriccion 1: Finishing
    if (2*x1 + x2 + 3*x3 > 99)
        return -1000;

    // Restriccion 2: Carpentry
    if (x1 + x2 + 0.5*x3 > 79)
        return -1000;

    // Restriccion 3: Demand
    if (x1 > 40)
        return -1000;

    // Funcion objetivo
    return 3*x1 + 2*x2 + 4*x3;
}

// -----------------------------------------------------------
// Muestra los valores decodificados de un individuo
// -----------------------------------------------------------
void muestraIndividuo(bool *cromosoma) {
    cout << "x1(soldier)=" << ctoInt(cromosoma, 0,  7);
    cout << " x2(train)=" << ctoInt(cromosoma, 8,  15);
    cout << " x3(nutty)=" << ctoInt(cromosoma, 16, 23);
    cout << " fitness="   << fitness(cromosoma);
    cout << endl;
}

// -----------------------------------------------------------
// main
// -----------------------------------------------------------
int main() {
    int i, j, g;
    srand(time(NULL));

    // --- Inicializacion de la poblacion ---
    // Limitamos cada variable a 6 bits efectivos (0-63) para que
    // la poblacion inicial tenga mayor probabilidad de ser valida.
    // Los 2 bits mas significativos de cada byte se ponen a 0.
    for (i = 0; i < M; i++) {
        for (j = 0; j < C; j++) {
            int bitEnByte = j % 8; // posicion del bit dentro del byte (0-7)
            if (bitEnByte >= 6)    // bits 6 y 7 -> forzar a 0
                individuo[i][j] = 0;
            else
                individuo[i][j] = rand() % 2;
        }
    }

    // --- Ciclo evolutivo ---
    for (g = 0; g < G; g++) {
        cout << "Generacion: " << g << endl;

        // --- SELECCION ---
        // Buscamos el primer individuo valido como punto de partida
        int best = -1;
        for (i = 0; i < M; i++) {
            if (fitness(individuo[i]) >= 0) {
                best = i;
                break;
            }
        }

        // Si ninguno es valido esta generacion, saltamos la reproduccion
        if (best == -1) {
            cout << "Generacion sin individuos validos, continuando..." << endl << endl;
            continue;
        }

        // Ahora buscamos el mejor entre los validos
        for (i = 0; i < M; i++) {
            if (fitness(individuo[i]) > fitness(individuo[best]))
                best = i;
        }

        // --- REPRODUCCION ---
        for (i = 0; i < M; i++) {
            if (i == best) continue; // el mejor se preserva intacto

            for (j = 0; j < C; j++) {
                // CRUZAMIENTO: con prob 0.5 tomamos el gen del mejor
                if (rand() % 2)
                    individuo[i][j] = individuo[best][j];
                // else conserva su propio gen

                // MUTACION: con prob 4% invertimos el bit
                if (rand() % 100 < 4)
                    individuo[i][j] = rand() % 2;
            }
        }

        cout << "La mejor adecuacion es: " << fitness(individuo[best]) << endl;
        muestraIndividuo(individuo[best]);
        cout << "Generacion completa" << endl << endl;

    } // fin ciclo evolutivo

    return 0;
} // main