#include <iostream>
using namespace std;

struct No {
    int valor;
    No *proximo;
};

void inserirFim(No *&head, int valor) {
    No *novo = new No();
    novo->valor = valor;
    novo->proximo = nullptr;

    if (head == nullptr) {
        head = novo;
        return;
    }

    No *atual = head;
    while (atual->proximo != nullptr) {
        atual = atual->proximo;
    }
    atual->proximo = novo;
}

void imprimirLista(No *head) {
    No *atual = head;
    while (atual != nullptr) {
        cout << atual->valor << " -> ";
        atual = atual->proximo;
    }
    cout << "NULL" << endl;
}

No *intersecao(No *L1, No *L2) {
    No *resultado = nullptr;
    No *ultimo = nullptr;

    while (L1 != nullptr && L2 != nullptr) {
        if (L1->valor == L2->valor) {
            No *novo = new No();
            novo->valor = L1->valor;
            novo->proximo = nullptr;

            if (resultado == nullptr) {
                resultado = novo;
            } else {
                ultimo->proximo = novo;
            }
            ultimo = novo;

            L1 = L1->proximo;
            L2 = L2->proximo;
        } else if (L1->valor < L2->valor) {
            L1 = L1->proximo;
        } else {
            L2 = L2->proximo;
        }
    }

    return resultado;
}

int main() {
    No *L1 = nullptr;
    No *L2 = nullptr;

    inserirFim(L1, 1);
    inserirFim(L1, 2);
    inserirFim(L1, 4);
    inserirFim(L1, 6);
    inserirFim(L1, 8);

    inserirFim(L2, 2);
    inserirFim(L2, 3);
    inserirFim(L2, 4);
    inserirFim(L2, 7);
    inserirFim(L2, 8);

    cout << "Lista L1: ";
    imprimirLista(L1);
    cout << "Lista L2: ";
    imprimirLista(L2);

    No *L3 = intersecao(L1, L2);
    cout << "Interseccao: ";
    imprimirLista(L3);

    return 0;
}