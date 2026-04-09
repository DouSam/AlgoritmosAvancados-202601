#include <iostream>
using namespace std;

int fatorial(int n) { 
    if (n <= 1) {
        return 1;
    }
    
    return n * fatorial(n - 1); 
}

int main() {
    int num = 5;
    cout << "O fatorial de " << num << " e: " << fatorial(num) << endl;
    return 0;
}