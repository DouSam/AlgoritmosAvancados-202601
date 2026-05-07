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

void printLots(No *L, No *P) {
    No *atualL = L;
    No *atualP = P;
    int posicaoAtual = 1;

    cout << "Elementos de L nas posicoes de P: ";
    while (atualL != nullptr && atualP != nullptr) {
        int posicaoDesejada = atualP->valor;

        if (posicaoDesejada < 1) {
            atualP = atualP->proximo;
            continue;
        }

        while (atualL != nullptr && posicaoAtual < posicaoDesejada) {
            atualL = atualL->proximo;
            posicaoAtual++;
        }

        if (atualL == nullptr) {
            break;
        }

        if (posicaoAtual == posicaoDesejada) {
            cout << atualL->valor << " ";
            atualP = atualP->proximo;
        }
    }
    cout << endl;
}

int main() {
    No *L = nullptr;
    No *P = nullptr;

    inserirFim(L, 20);
    inserirFim(L, 40);
    inserirFim(L, 10);
    inserirFim(L, 15);

    inserirFim(P, 1);
    inserirFim(P, 2);
    inserirFim(P, 4);
    inserirFim(P, 10);

    cout << "Lista L: ";
    imprimirLista(L);
    cout << "Lista P: ";
    imprimirLista(P);

    printLots(L, P);

    return 0;
}