#include <math.h>
#include <stdio.h>
#include <iostream>

double inf=1.0/0.0 ;

using namespace std;

class matriz{
  private:
    int n; // matriz cuadrada de nxn
    int i,j,k; // índices
    double **a;
    double **from; //Matriz from: de donde vienen los nodos
  public:
  matriz(int n); //Constructor
  ~matriz(); //destructor
  void lee();
  void muestra();
  void fw();
  int fr(int o, int d); //Encuentra ruta de origen a destino
};

matriz::matriz(int nn=1){
  n=nn+1; //Aumentamos en 1 para que empiece de 1 y no de 0 
  a=new double * [n];
  from=new double * [n];
  for(i=1; i<n; i++){
    a[i]=new double[n];
    from[i]=new double[n];
  }
}

matriz::~matriz(){
  for(i=1; i<n; i++){
    delete a[i];
    delete from[i];
  }
  delete a ;
  delete from ;
}

void matriz::lee(){
  for(i=1; i<n; i++){ 
    for(j=1; j<n; j++){ 
      //cout<<"["<<i<<","<<j<<"]=";
      scanf("%lf", &a[i][j]); //Para double es necesario "%lf"
      if (i==j) //Siempre del mismo nodo al mismo no la d=0
        a[i][j]=0;
      if ( a[i][j]!=inf)
        from[i][j]=j; //Al nodo j se llega por medio del mismo j 
      else
        from[i][j]=-1; //Puede ser -1 o inf
    }
  }
}

void matriz::muestra(){
    printf("%4s "," ");
    for(j=1; j<n; j++){ 
      printf("%4d",j);
    }
    cout<<" | ";
    for(j=1; j<n; j++){ 
      printf("%4d",j);
    }
    cout<<"\n\n";
  
  for(i=1; i<n; i++){ 
    printf("%4d|",i); 
    for(j=1; j<n; j++){ 
      printf("%4.0f",a[i][j]);;
    }
    cout<<" | ";
    for(j=1; j<n; j++){ 
      printf("%4.0f",from[i][j]);;
    }
    cout<<"\n";
  }
}

void matriz::fw(){
 for(k=1; k<n; k++){ 
  cout<<"\nk="<<k<<"\n";
  for(i=1; i<n; i++){ 
    for(j=1; j<n; j++){ 
      if ( a[i][k]+a[k][j]< a[i][j] ){
        a[i][j]=a[i][k]+a[k][j];
        // agregar operación de matriz from[i][j]
      }
    }
  }
  muestra();
 }
}//fw

int matriz::fr(int o, int d){
    printf("Ruta desde: %d hasta: %d distancia:%4.0lf\n",o,d,a[o][d]);

    if( from[o][d] < 0 ) {
      printf("¡No hay ruta desde %4d hasta %4d!\n",o,d);
      return(1);
    }

    i=o; //Guardamos inicio
    while(o!=from[o][d]){
         cout<<o<<" -> ";
         o=from[o][d];
      } 
      cout<<d<<"\n";
    double dis=0; 
    o=i; j=o; 
    while(o!=from[o][d]){
         o=from[o][d];
         dis=a[j][o];
         j=o;
         printf("%3.0lf %1s",dis," "); 
      } 
    printf("\n");

  return(0);
}

int main(){
   int n;
   cout<<"Número de vértices (nodos): \n";
   cin>>n;
   matriz m(n);
   m.lee();
   m.muestra();
   m.fw();

   double o,d;
   cout<<"Origen:";   cin>>o;
   cout<<"Destino:";  cin>>d;

   m.fr(o,d);
}