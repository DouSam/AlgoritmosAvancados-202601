#include <iostream>
using namespace std;

struct No {
    int valor;
    No *proximo; 
};

void imprimirIterativo(No* head) {
    No* atual = head;
    while (atual != nullptr) {
        cout << atual->valor << " -> ";
        atual = atual->proximo;
    }
    cout << "NULL" << endl;
}

void imprimirRecursivo(No* atual) {
    // Caso Base: Se chegou no fim da lista
    if (atual == nullptr) {
        cout << "NULL" << endl;
        return;
    }
    
    // Processamento
    cout << atual->valor << " -> ";
    
    // Progresso: Chama para o próximo nó 
    imprimirRecursivo(atual->proximo);
}

int main() {
    No *n1 = new No(); 
    No *n2 = new No();
    No *n3 = new No();

    n1->valor = 10; n1->proximo = n2;
    n2->valor = 20; n2->proximo = n3;
    n3->valor = 30; n3->proximo = nullptr;

    cout << "Impressao Iterativa:" << endl;
    imprimirIterativo(n1);

    cout << "Impressao Recursiva:" << endl;
    imprimirRecursivo(n1);

    return 0;
}