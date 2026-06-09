#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>

double circulo(double x, double y, double z) {
  return x*x + y*y + z*z;
}

double randomReal(double min, double max){
  return (double )rand()/RAND_MAX * (max-min)+min;
}


int main(){
   int radio=1;
   unsigned long int N=1e8, n=0;

   double aprox, x, y, z, Vcaja;  // A - Área de la caja , aprox- area desconocida

   srand(time(NULL));

   for(int i=0; i<N; i++){
     x=randomReal(-radio, radio);
     y=randomReal(-radio, radio);
     z=randomReal(-radio, radio);
     if (circulo(x,y,z)<=radio*radio){
        n++;
     }

   }

   Vcaja =8.0 * radio * radio * radio;
   aprox= Vcaja * (double)n / (double)N;

   cout<<"Volumen Aprox="<<aprox<<endl;
   cout<<"Incidencias="<<n<<endl;
   cout<<"Total puntos="<<N<<endl;
}
