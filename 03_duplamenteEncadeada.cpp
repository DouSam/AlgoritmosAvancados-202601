#include <iostream>
using namespace std;

// 1. A Estrutura do Nó
struct NoDuplo {
    int valor;
    NoDuplo* anterior;
    NoDuplo* proximo;
};

// 2. Inicializando a lista com Sentinelas (Head e Tail vazios)
void inicializarLista(NoDuplo* &head, NoDuplo* &tail) {
    head = new NoDuplo(); // Nó sentinela de início
    tail = new NoDuplo(); // Nó sentinela de fim
    
    head->proximo = tail; // Head aponta para o Tail
    tail->anterior = head; // Tail aponta de volta para o Head
    
    head->anterior = nullptr;
    tail->proximo = nullptr;
}

// 3. Inserindo no Fim 
void inserirFim(NoDuplo* tail, int v) {
    // Pede um novo nó no Heap
    NoDuplo* novo = new NoDuplo();
    novo->valor = v;
    
    novo->anterior = tail->anterior; // Novo aponta para o antigo último nó
    novo->proximo = tail;            // Novo aponta para frente (para o Tail)
    
    tail->anterior->proximo = novo;  // O antigo último nó aponta para o novo
    tail->anterior = novo;           // O Tail agora aponta para trás (para o novo)
}

void imprimirLista(NoDuplo* head) {
    NoDuplo* temp = head->proximo; // Começa pelo primeiro nó real (após o Head)
    cout << "Lista Duplamente Encadeada: ";
    while (temp->proximo != nullptr) { // Enquanto não chegar no Tail
        if (temp->anterior != nullptr) {
            cout << temp->valor << "(" << temp->anterior->valor << ")" << " <- "; // Imprime o valor do nó atual e anterior
        } else {
            cout << temp->valor << " <- "; // Para o primeiro nó, não tem anterior
        }
        temp = temp->proximo;
    }
    cout << "NULL" << endl;
}

int main() {
    NoDuplo *head, *tail;
    inicializarLista(head, tail);
    
    inserirFim(tail, 10);
    inserirFim(tail, 20);
    inserirFim(tail, 30);

    imprimirLista(head);

    return 0;
}