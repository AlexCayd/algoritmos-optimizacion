// exp. 00123456 Miguel Angel Mendez Mendez


#include <iostream> //cin, cout
#include <stdlib.h> //srand, rand
#include <time.h> //srand, rand

using namespace std;

char ingrediente[][20]= {"sal","azucar","limon","huevo","agua","cebolla","manzana"};


int fitness(bool * cromosoma){ // la información de los cromosomas crean al individuo

 
//declaramos un apuntador, la funcion va a valorar el individuo segun los valores de los cromosomas--> bool * cromosoma es un individuo
// ingredientes 0-sal,1-azucar,....6-manzana
    int value;
value=-cromosoma[0]+cromosoma[1]+cromosoma[2]
      -cromosoma[3]+cromosoma[4]-cromosoma[5]-cromosoma[6];
// características deseables con valor +, los no deseados con valor - esta es la funcion de fitnes la que restringe
return value;
}


void muestraindividuo(bool * cromosoma){
  // nos sirve para visualizar los 7 cromosomas del individuo
    int j;//contrador de cromosomas

    for(j=0; j<7;j++){// nos despliega los genes 0 1 0 ...
        cout<<j<<":"<<cromosoma[j]<<" ";
    }
    cout<<endl;

    for(j=0; j<7;j++){//nos despliega ingredientes
        if(cromosoma[j])
        cout<<ingrediente[j]<<" ";
    }

    cout<<endl;

}


int main(){

    int i,j,g;// individuos, cromosomas, generaciones(contadores)

    int nindividuos=10;//numero de individuos por generacion
    int ncromosomas=7;
    bool generacion[10][7];//Cada generaciión tiene 10 individuos con 7 cromosomas cada uno

    int best=0;
    srand(time(NULL));//inicializamos generador de numero aleatorios

//inicializamos la poblacion (generación)
    for(i=0;i<nindividuos;i++) //Número de idividuos ( 10 )
        for(j=0;j<ncromosomas;j++) //Numero de cromosomas por individuo
        generacion[i][j]=rand()%2; // generamos la poblacion inicial de 10 individuos
                                   // 7 cromosomas por individuo

//ciclo evolutivo
    for(g=0;g<100;g++){//100 generaciones maximo
    cout<<"Generacion:"<<g<<endl;

    //SELECCION
    best=0; // El primer individuo es el mejor
        for(i=0;i<nindividuos;i++){
          if (fitness(generacion[best])<fitness(generacion[i])) // multiplica 7*i por default, apuntador bloque de memoria, verifica los valores de individuo
            best=i;
          }

    //REPRODUCCION
        for(i=0;i<nindividuos;i++){
            if(i!=best){//si es diferente del mejor
              for(j=0;j<ncromosomas;j++){//CRUZAMIENTO
                if(rand()%2) 
                // con probabilidad de 1 entre 2=.5 compara cada cromosoma 
                // del best y del nuevo individuo genero al nuevo individuo
                    generacion[i][j]=generacion[best][j];
                else
                    generacion[i][j]=generacion[i][j];

    //MUTACION
                if(rand()%100<4)
                // con probabilidad de 1 entre 25 ( 4 % )  
                // Muta (cambia ) el bit del cromosoma
                //generacion[i][j]=rand()%2; 
                    //El valor es aleatorio, pero podríamos invertir el valor:
                    generacion[i][j]^=1; 
              }//for de cromomosomas
            }//if
        }//for de individuos

   cout<<"best="<<best<<" La mejor adecuacion es:"<<fitness(generacion[best])<<endl;
    muestraindividuo(generacion[best]);//muestra individuo
    cout<<"Generación completa"<<endl;
    for(i=0;i<10;i++){
        cout<<"["<<i<<"]: ";
        muestraindividuo(generacion[i]);
    }
    cout<<endl<<endl;    

    }//fin evolucion
}//main
