#include <iostream>

using namespace std;

struct No {
    int valor;
    No *proximo; 
};

// Para filas encadeadas, precisamos controlar o INÍCIO e o FIM
void enqueue(No* &frente, No* &fim, int v) {
    No* novo = new No();
    novo->valor = v;
    novo->proximo = nullptr;
    
    if (fim != nullptr) {
        fim->proximo = novo; // O antigo último aponta para o novo
    }
    fim = novo; // Atualiza o ponteiro de fim
    
    if (frente == nullptr) {
        frente = novo; // Se a fila estava vazia, o novo é também a frente
    }
}

void dequeue(No* &frente, No* &fim) {
    if (frente == nullptr) return; // Fila vazia
    
    No* temp = frente;
    frente = frente->proximo; // A frente avança para o próximo da fila
    
    if (frente == nullptr) {
        fim = nullptr; // Se a fila esvaziou, o fim também deve ser nulo
    }
    delete temp;
}

int main() {
    No* frente = nullptr; // Início da fila
    No* fim = nullptr;   // Fim da fila

    enqueue(frente, fim, 10);
    enqueue(frente, fim, 20);
    enqueue(frente, fim, 30);

    cout << "Frente da fila: " << frente->valor << endl; // Deve mostrar 10

    dequeue(frente, fim);
    cout << "Frente da fila apos um dequeue: " << frente->valor << endl; // Deve mostrar 20

    return 0;
}