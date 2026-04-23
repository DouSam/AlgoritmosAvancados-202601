#include <iostream>
using namespace std;

struct No {
    int valor;
    No *proximo; 
};

// Função PUSH (Empilhar - Inserir no topo)
void push(No* &topo, int v) {
    No* novo = new No();
    novo->valor = v;
    novo->proximo = topo;
    topo = novo;
}

// Função POP (Desempilhar - Remover do topo)
void pop(No* &topo) {
    if (topo == nullptr) return; // Pilha vazia
    
    No* temp = topo;
    topo = topo->proximo; // O topo passa a ser o elemento de baixo
    delete temp;          // Libera a memória
}

int main() {
    No* topo = nullptr; // Pilha inicialmente vazia

    push(topo, 10);
    push(topo, 20);
    push(topo, 30);

    cout << "Topo da pilha: " << topo->valor << endl; // Deve mostrar 30

    pop(topo);
    cout << "Topo da pilha apos um pop: " << topo->valor << endl; // Deve mostrar 20

    return 0;
}