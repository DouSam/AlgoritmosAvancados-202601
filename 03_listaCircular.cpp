#include <iostream>
using namespace std;

struct No { 
    int valor; 
    No *proximo; 
};

void inserirCircular(No* &head, int valor) {
    No* novo = new No();
    novo->valor = valor;
    if (head == nullptr) {
        head = novo;
        head->proximo = head; // Aponta para si mesmo
    } else {
        No* temp = head;
        while (temp->proximo != head) { // Encontra o último nó
            temp = temp->proximo;
        }
        temp->proximo = novo; // Último nó aponta para o novo nó
        novo->proximo = head; // Novo nó aponta para o início
    }
}

void imprimirCircular(No* head) {
    if (head == nullptr) {
        cout << "Lista vazia!" << endl;
        return;
    }
    No* atual = head;
    do {
        cout << atual->valor << " -> ";
        atual = atual->proximo;
    } while (atual != head); // Continua até voltar ao início
    cout << "(volta ao início)" << endl;
}

int main(){
    No* head = nullptr; // Lista circular inicialmente vazia

    inserirCircular(head, 10);
    inserirCircular(head, 20);
    inserirCircular(head, 30);

    imprimirCircular(head);

    return 0;
}