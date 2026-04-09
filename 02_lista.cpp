#include <iostream>
using namespace std;

struct No {
    int valor;
    No *proximo; 
};

// EX 1
void inserirFim(No* &head, int v) {
    No* novo = new No(); 
    novo->valor = v;
    novo->proximo = nullptr;

    if (head == nullptr) { 
        head = novo;
        return;
    }

    No* temp = head;
    while (temp->proximo != nullptr) { 
        temp = temp->proximo;
    }
    temp->proximo = novo;
}

//EX 2
void contagemRegressiva(int n) {
    if (n < 0) return;

    cout << "Empilhando: " << n << endl;
    contagemRegressiva(n - 1);
    cout << "Desempilhando: " << n << endl;
}

//EX 3

//EX 4
void imprimirReverso(No* atual) {
    if (atual == nullptr) return;

    imprimirReverso(atual->proximo); 
    cout << atual->valor << " <- "; 
}

//EX 5
void inserirApos(No* anterior, int v) {
    if (anterior == nullptr) return;

    No* novo = new No();
    novo->valor = v;
    novo->proximo = anterior->proximo; 
    anterior->proximo = novo;
}

//EX 6
bool buscarNaLista(No* head, int alvo) {
    No* atual = head;
    while (atual != nullptr) { 
        if (atual->valor == alvo) return true;
        atual = atual->proximo; 
    }
    return false;
}

//EX 7
void buscarERemover(No* &head, int alvo) {
    if (head == nullptr) return;

    // Caso o alvo seja o primeiro nó
    if (head->valor == alvo) {
        No* temp = head;
        head = head->proximo; // Redireciona a cabeça
        delete temp;          // Limpa o Heap
        return;
    }

    No* atual = head;
    // Busca o nó ANTERIOR ao que queremos remover
    while (atual->proximo != nullptr && atual->proximo->valor != alvo) {
        atual = atual->proximo;
    }

    if (atual->proximo != nullptr) {
        No* alvoNo = atual->proximo;
        atual->proximo = alvoNo->proximo; // Pula o nó alvo
        delete alvoNo; // Limpa o nó da memória
    }
}

int main() {
    return 0;
}