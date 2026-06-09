#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <iostream>
using namespace std;

// Función para generar un número real aleatorio en un rango dado
double randomReal(double min, double max){
  return (double)rand() / RAND_MAX * (max - min) + min;
}

// Función implícita de la curva x^2 + y^2 + sin(2x + 2y) - 10
double f(double x, double y){
  return x*x + y*y + sin(2*x + 2*y) - 10;
}

int main(){
   int i;
   long int Total = 1000000;  // Número de puntos aleatorios
   long int Adentro = 0;      // Contador de puntos dentro de la región

   double x, y;
   double area, areaconocida;

   srand(time(NULL));  // Inicializar la semilla aleatoria
   
   for(i = 0; i < Total; i++){
     x = randomReal(-2.0, 2.0);  // Generar x en [-2,2]
     y = randomReal(0.0, 4.0);   // Generar y en [0,4]
     
     if (f(x, y) <= 0)  // Verificar si el punto está dentro de la región
       Adentro++;
   }
   
   areaconocida = (2 - (-2)) * (4 - 0);  // Área del rectángulo
   area = areaconocida * Adentro / Total;  // Cálculo del área con Montecarlo
   
   cout << "El área aproximada es: " << area << " unidades cuadradas" << endl;
   
   return 0;
}
