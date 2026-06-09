#include <iostream> // Habilita cout
#include <cstdlib> // Habilita rand(), srand() y RAND_MAX
#include <cmath> // Habilita pow()
#include <ctime> // Habilita time(NULL) para la semilla

using namespace std;

// Convertir un num aleatorio 0-1 en uno entre min y max
double randomReal(double min, double max) {
    return min + (double)rand() / RAND_MAX * (max - min);
}

int main() {
    srand(time(NULL)); // Generación de semilla, se usa srand en lugar de rand para que genere una secuencia diferente cada que se inicia el programa

    long long N = 100000; // Número de puntos a generar
    
    for (int d = 1; d <= 7; d++) {
        long long puntosDentroEsfera = 0; // Contador de puntos dentro de la esfera
        
        // Se repite N veces
        for (long long i = 0; i < N; i++) {
            double sumsq = 0.0;

            // Calcular si el punto cae dentro
            for (int k = 0; k < d; k++) {
                double x = randomReal(-1.0, 1.0);
                sumsq += x * x;
            }

            // Contar si está dentro
            if (sumsq <= 1.0) puntosDentroEsfera++;
        }

        // Vaprox = Vcaja * (puntosDentroEsfera/N)
        double Vcaja = pow(2.0, d);
        double Vaprox = Vcaja * (double)puntosDentroEsfera / N;

        cout << "d = " << d << endl;
        cout << "Volumen aproximado = " << Vaprox << endl;

    }

    
    return 0;
}