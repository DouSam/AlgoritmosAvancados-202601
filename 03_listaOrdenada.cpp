#include <iostream>
using namespace std;

struct No {
    int valor;
    No *proximo; 
};

void inserirOrdenado(No* &head, int v) {
    No* novo = new No();
    novo->valor = v;

    // Caso 1: Lista vazia ou o novo valor é o menor de todos (vai para o início)
    if (head == nullptr || head->valor >= v) {
        novo->proximo = head;
        head = novo;
        return;
    }

    // Caso 2: Procurar a posição correta no meio ou fim
    No* atual = head;
    while (atual->proximo != nullptr && atual->proximo->valor < v) {
        atual = atual->proximo;
    }
    
    // Conectar o novo nó na posição encontrada
    novo->proximo = atual->proximo;
    atual->proximo = novo;
}

void imprimirLista(No* head) {
    No* atual = head;
    cout << "Lista Ordenada: ";
    while (atual != nullptr) {
        cout << atual->valor << " -> ";
        atual = atual->proximo;
    }
    cout << "NULL" << endl;
}

int main() {
    No* head = nullptr;

    inserirOrdenado(head, 30);
    inserirOrdenado(head, 10);
    inserirOrdenado(head, 35);
    inserirOrdenado(head, 20);

    imprimirLista(head);

    return 0;
}