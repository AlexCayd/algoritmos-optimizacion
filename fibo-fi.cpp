#include <iostream>
using namespace std;

unsigned long long int fibod(int n){ 
    static unsigned long long int r[10000000];

    if (r[n] > 0) return r[n];

    if(n == 1 || n == 0) 
        r[n] = 1;
    else 
        r[n] = fibod(n-1) + fibod(n-2);

    return r[n];
}

int main(){
    int n;
    cout << "Dame el numero de terminos de Fibo: ";
    cin >> n;

    unsigned long long int Fn = fibod(n);
    unsigned long long int Fn1 = fibod(n + 1);

    long double phi = (long double)Fn1 / Fn;

    cout << "Aproximacion de phi = " << phi << endl;

    return 0;
}
