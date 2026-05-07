#include <iostream>
using namespace std;

struct No {
    int valor;
    No *proximo;
};

void inserirCircular(No *&head, int valor) {
    No *novo = new No();
    novo->valor = valor;

    if (head == nullptr) {
        head = novo;
        head->proximo = head;
        return;
    }

    No *atual = head;
    while (atual->proximo != head) {
        atual = atual->proximo;
    }

    atual->proximo = novo;
    novo->proximo = head;
}

void imprimirCircular(No *head) {
    if (head == nullptr) {
        cout << "Lista vazia" << endl;
        return;
    }

    No *atual = head;
    do {
        cout << atual->valor << " -> ";
        atual = atual->proximo;
    } while (atual != head);
    cout << "(volta ao inicio)" << endl;
}

void percorrerNvezes(No *head, int vezes) {
    if (head == nullptr || vezes <= 0) {
        return;
    }

    No *atual = head;
    for (int i = 0; i < vezes; i++) {
        cout << "Percurso " << (i + 1) << ": ";
        do {
            cout << atual->valor << " ";
            atual = atual->proximo;
        }
        while (atual != head);
        
        cout << endl;
    }
}

int main() {
    No *head = nullptr;

    inserirCircular(head, 10);
    inserirCircular(head, 20);
    inserirCircular(head, 30);
    inserirCircular(head, 40);

    imprimirCircular(head);
    percorrerNvezes(head, 3);

    return 0;
}