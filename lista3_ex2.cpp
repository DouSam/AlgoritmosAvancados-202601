#include <iostream>
using namespace std;

struct NoDuplo {
    int valor;
    NoDuplo *anterior;
    NoDuplo *proximo;
};

void inicializarLista(NoDuplo *&head, NoDuplo *&tail) {
    head = new NoDuplo();
    tail = new NoDuplo();

    head->anterior = nullptr;
    head->proximo = tail;
    tail->anterior = head;
    tail->proximo = nullptr;
}

void inserirFim(NoDuplo *tail, int valor) {
    NoDuplo *novo = new NoDuplo();
    novo->valor = valor;

    novo->anterior = tail->anterior;
    novo->proximo = tail;

    tail->anterior->proximo = novo;
    tail->anterior = novo;
}

void imprimirLista(NoDuplo *head) {
    NoDuplo *atual = head->proximo;
    cout << "Lista: ";
    while (atual->proximo != nullptr) {
        cout << atual->valor << " <-> ";
        atual = atual->proximo;
    }
    cout << "NULL" << endl;
}

bool trocarAdjacentes(NoDuplo *head, NoDuplo *tail, int valor) {
    NoDuplo *atual = head->proximo;

    while (atual != tail && atual->valor != valor) {
        atual = atual->proximo;
    }

    if (atual == tail || atual->proximo == tail) {
        return false;
    }

    NoDuplo *proximo = atual->proximo;
    NoDuplo *anterior = atual->anterior;
    NoDuplo *depois = proximo->proximo;

    anterior->proximo = proximo;
    proximo->anterior = anterior;

    proximo->proximo = atual;
    atual->anterior = proximo;

    atual->proximo = depois;
    depois->anterior = atual;

    return true;
}

int main() {
    NoDuplo *head, *tail;
    inicializarLista(head, tail);

    inserirFim(tail, 10);
    inserirFim(tail, 20);
    inserirFim(tail, 30);
    inserirFim(tail, 40);

    cout << "Antes da troca: ";
    imprimirLista(head);

    if (trocarAdjacentes(head, tail, 20)) {
        cout << "Depois da troca do no 20 com o proximo: ";
        imprimirLista(head);
    } else {
        cout << "Troca nao realizada." << endl;
    }

    return 0;
}