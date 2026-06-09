#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* Prototipos de la libreria externa */
double r8_normal_01_cdf_inverse(double p);
double r8poly_value(int n, double a[], double x);
double r8_huge(void);

/* Incluir implementacion */
#include "asa241.c"

/* Generador de variables aleatorias con distribucion normal */
double normal_rand(double mean, double stddev) {
    double u;
    do {
        u = (double)rand() / ((double)RAND_MAX + 1.0);
    } while (u <= 0.0 || u >= 1.0);
    return mean + stddev * r8_normal_01_cdf_inverse(u);
}

int main(void) {
    long i;
    long N = 1000000; 
    double COSTO = 400000.0;
    double GAM_MIN = 100000.0; 
    double PER_MAX = -100000.0; 

    /* Definicion de medias y desviaciones (IC 90%) */
    double MS_mean  = 15.0,    MS_std  = 10.0 / 3.29; 
    double LS_mean  = 3.0,     LS_std  = 10.0 / 3.29; 
    double RMS_mean = 6.0,     RMS_std = 6.0 / 3.29;  
    double PL_mean  = 25000.0, PL_std  = 20000.0 / 3.29;

    long cnt_ganancia = 0;
    long cnt_perdida = 0;

    double suma_ahorro = 0.0, suma_ahorro2 = 0.0;
    double ahorro_min = 1e18, ahorro_max = -1e18;

    srand((unsigned)time(NULL));

    printf("Iniciando Simulacion Monte Carlo: %ld escenarios\n", N);
    printf("Costo de la maquina: $%.2f\n\n", COSTO);

    for (i = 0; i < N; i++) {
        double MS  = normal_rand(MS_mean,  MS_std);
        double LS  = normal_rand(LS_mean,  LS_std);
        double RMS = normal_rand(RMS_mean, RMS_std);
        double PL  = normal_rand(PL_mean,  PL_std);

        double ahorro = (MS + LS + RMS) * PL;
        double resultado = ahorro - COSTO;

        suma_ahorro  += ahorro;
        suma_ahorro2 += ahorro * ahorro;
        
        if (ahorro < ahorro_min) ahorro_min = ahorro;
        if (ahorro > ahorro_max) ahorro_max = ahorro;

        if (resultado >= GAM_MIN) cnt_ganancia++;
        if (resultado >= PER_MAX) cnt_perdida++;
    }

    double media_ahorro = suma_ahorro / N;
    double std_ahorro = sqrt(suma_ahorro2 / N - media_ahorro * media_ahorro);

    printf("=== RESULTADOS ===\n");
    printf("Ahorro Anual:\n");
    printf("  Media:          $%.2f\n", media_ahorro);
    printf("  Desv. Estandar: $%.2f\n", std_ahorro);
    printf("  Rango:          [$%.2f , $%.2f]\n\n", ahorro_min, ahorro_max);

    double p1 = (double)cnt_ganancia / N;
    double p2 = (double)cnt_perdida / N;

    printf("Probabilidades:\n");
    printf("  P(Ganancia >= 100k): %.4f (%.2f%%)\n", p1, p1 * 100.0);
    printf("  P(Perdida <= 100k):  %.4f (%.2f%%)\n", p2, p2 * 100.0);
    printf("==================\n");

    return 0;
}