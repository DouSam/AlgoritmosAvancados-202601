#include <iostream>
using namespace std;

struct No {
    int valor;
    No *proximo; 
};

void inserirInicio(No* &head, int valor){
    No* novo = new No();
    novo->valor = valor;
    novo->proximo = nullptr;

    if(head == nullptr){
        head = novo;
    } else {
        novo->proximo = head;
        head = novo;
    }
}

void inserirFim(No* &head, int valor){
    No* novo = new No();
    novo->valor = valor;
    novo->proximo = nullptr;

    if(head == nullptr){
        head = novo;
    }else {
    No* temp = head;
    while(temp->proximo != nullptr){
        temp = temp->proximo;
    }
    temp->proximo = novo;
    }
}

void imprimirLista(No* head) {
    No* atual = head;
    while (atual != nullptr) {
        cout << atual->valor << "(" << atual << ")" << " -> ";
        atual = atual->proximo;
    }
    cout << "NULL" << endl;
}

int main() {
    No* head = nullptr;
    
    int opcao, valor;
    do {
        cout << "Menu:" << endl;
        cout << "0. Inserir no inicio" << endl;
        cout << "1. Inserir no fim" << endl;
        cout << "2. Imprimir lista" << endl;
        cout << "3. Imprimir reverso" << endl;
        cout << "4. Inserir apos" << endl;
        cout << "5. Buscar na lista" << endl;
        cout << "6. Remover da lista" << endl;
        cout << "10. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 0:
                cout << "Digite um valor para inserir: ";
                cin >> valor;
                inserirInicio(head, valor);
                cout << "Valor inserido no inicio: " << valor << endl;
                break;
            case 1:
                cout << "Digite um valor para inserir: ";
                cin >> valor;
                inserirFim(head, valor);
                cout << "Valor inserido no fim: " << valor << endl;
                break;
            case 2:
                imprimirLista(head);
                break;
            case 10:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }

    } while (opcao != 10);

    return 0;
}