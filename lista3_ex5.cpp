#include <iostream>
using namespace std;

struct No {
    int valor;
    No *anterior;
    No *proximo;
};

struct ListaDupla {
    No *head;
    No *tail;
};

void inicializarLista(ListaDupla &lista) {
    lista.head = new No();
    lista.tail = new No();

    lista.head->anterior = nullptr;
    lista.head->proximo = lista.tail;
    lista.tail->anterior = lista.head;
    lista.tail->proximo = nullptr;
}

No *begin(ListaDupla &lista) {
    return lista.head->proximo;
}

No *end(ListaDupla &lista) {
    return lista.tail;
}

bool vazia(const ListaDupla &lista) {
    return lista.head->proximo == lista.tail;
}

void inserirFim(ListaDupla &lista, int valor) {
    No *novo = new No();
    novo->valor = valor;

    novo->anterior = lista.tail->anterior;
    novo->proximo = lista.tail;

    lista.tail->anterior->proximo = novo;
    lista.tail->anterior = novo;
}

void imprimir(const ListaDupla &lista) {
    No *atual = lista.head->proximo;
    while (atual != lista.tail) {
        cout << atual->valor << " <-> ";
        atual = atual->proximo;
    }
    cout << "NULL" << endl;
}

void splice(int valorPosicao, ListaDupla &listaDestino, ListaDupla &listaOrigem) {
    if (vazia(listaOrigem)) {
        return;
    }

    No *posicao = listaDestino.head->proximo;
    while (posicao != listaDestino.tail && posicao->valor != valorPosicao) {
        posicao = posicao->proximo;
    }

    if (posicao == listaDestino.tail) {
        return;
    }

    No *primeiro = listaOrigem.head->proximo;
    No *ultimo = listaOrigem.tail->anterior;
    No *proximoPosicao = posicao->proximo;

    posicao->proximo = primeiro;
    primeiro->anterior = posicao;

    ultimo->proximo = proximoPosicao;
    proximoPosicao->anterior = ultimo;

    listaOrigem.head->proximo = listaOrigem.tail;
    listaOrigem.tail->anterior = listaOrigem.head;
}

int main() {
    ListaDupla listaA;
    ListaDupla listaB;
    inicializarLista(listaA);
    inicializarLista(listaB);

    inserirFim(listaA, 10);
    inserirFim(listaA, 20);
    inserirFim(listaA, 50);

    inserirFim(listaB, 30);
    inserirFim(listaB, 40);

    cout << "Lista A antes do splice: ";
    imprimir(listaA);
    cout << "Lista B antes do splice: ";
    imprimir(listaB);

    splice(20, listaA, listaB);

    cout << "Lista A depois do splice antes do fim: ";
    imprimir(listaA);
    cout << "Lista B depois do splice: ";
    imprimir(listaB);

    return 0;
}