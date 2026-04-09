#include <iostream>
using namespace std;

int fatorial(int n) { 
    int resultado = 1;
    for (int i = n; i > 1; i--) {
        resultado *= i;
    }
    return resultado;
}

int main() {
    int num = 5;
    cout << "O fatorial de " << num << " e: " << fatorial(num) << endl;
    return 0;
}