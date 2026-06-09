#include <iostream>

using namespace std;

// Obtengamos los valores con infinitos
double inf = 1.0 / 0.0;
double menosinf = -1.0 / 0.0;

int main() {
    double r;
    cout << "inf: " << inf << "\n";
    cout << "-inf: " << menosinf << "\n";
    r = inf + menosinf;
    cout << "suma: " << r << "\n";
}