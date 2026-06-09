#include <iostream>
using namespace std;

unsigned long int fibo (unsigned long int n) {
    if((n==1) or (n==0)) {
        return (1);
    } else {
        return (fibo(n-1)+fibo(n-2));
    }
}

int main() {
    unsigned long int n, r;
    cout << "Dame n = \n";
    cin >> n;
    r = fibo(n);
    cout << "Resultado" << r << "\n";
}