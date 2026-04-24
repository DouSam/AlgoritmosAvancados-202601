#include <iostream>
using namespace std;

struct NoDuplo {
    int valor;
    NoDuplo *proximo;
    NoDuplo *anterior;
};

void inicializarLista(NoDuplo* &head, NoDuplo* &tail) {
    head = new NoDuplo();
    tail = new NoDuplo();
    
    head->proximo = tail;
    head->anterior = nullptr;

    tail->proximo = nullptr;
    tail->anterior = head;
}

int main() {
    NoDuplo* head = nullptr;
    NoDuplo* tail = nullptr;

    inicializarLista(head, tail);
    
    int opcao, valor;
    do {
        cout << "Menu - Lista Duplamente Encadeada:" << endl;
        cout << "0. Inserir no inicio" << endl;
        cout << "1. Inserir no fim" << endl;
        cout << "2. Imprimir lista (frente para tras)" << endl;
        cout << "3. Imprimir lista (tras para frente)" << endl;
        cout << "4. Inserir antes de um valor" << endl;
        cout << "5. Buscar na lista" << endl;
        cout << "6. Remover da lista" << endl;
        cout << "7. Limpar a lista" << endl;
        cout << "10. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 0:
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }

    } while (opcao != 10);

    return 0;
}