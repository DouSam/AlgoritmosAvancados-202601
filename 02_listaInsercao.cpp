#include <iostream>
using namespace std;

struct No {
    int valor;
    No *proximo; 
};

void imprimirRecursivo(No* atual) {
    // Caso Base: Se chegou no fim da lista
    if (atual == nullptr) {
        cout << "NULL" << endl;
        return;
    }
    
    // Processamento
    cout << atual->valor << " -> ";
    
    // Progresso: Chama para o próximo nó 
    imprimirRecursivo(atual->proximo);
}

// Função para inserir no início (O(1))
void inserirInicio(No* &head, int v) {
    No* novo = new No();
    novo->valor = v;
    novo->proximo = head; // O novo nó aponta para quem era o primeiro
    head = novo;          // A "cabeça" da lista agora é o novo nó
}

void removerInicio(No* &head) {
    if (head == nullptr) {
        cout << "Lista vazia, nada para remover." << endl;
        return;
    }

    // 1. Guardamos o endereço do nó que será removido
    No* temp = head;

    // 2. Fazemos a head apontar para o próximo elemento
    head = head->proximo;

    // 3. Deletamos o nó da memória Heap
    delete temp; 
    cout << "No removido do inicio." << endl;
}

int main() {
    No *n1 = new No(); 
    No *n2 = new No();
    No *n3 = new No();

    n1->valor = 10; n1->proximo = n2;
    n2->valor = 20; n2->proximo = n3;
    n3->valor = 30; n3->proximo = nullptr;

    imprimirRecursivo(n1);
    
    inserirInicio(n1, 5); 
    cout << "Apos inserir 5 no inicio:" << endl;
    imprimirRecursivo(n1);
    
    removerInicio(n1);
    cout << "Apos remover do inicio:" << endl;
    imprimirRecursivo(n1);

    return 0;
}