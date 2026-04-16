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

void imprimirReverso(No* head) {
    if (head == nullptr) {
        return;
    }
    imprimirReverso(head->proximo);
    cout << head->valor << "(" << head << ")" << " -> ";
}

void inserirApos(No* head, int valor_anterior, int valor){
    No* atual = head;
    while (atual != nullptr && atual->valor != valor_anterior) {
        atual = atual->proximo;
    }
    if (atual == nullptr) {
        cout << "Valor anterior nao encontrado!" << endl;
        return;
    }
    No* novo = new No();
    novo->valor = valor;
    novo->proximo = atual->proximo;
    atual->proximo = novo;
}

int buscarNaLista(No* head, int valor) {
    No* atual = head;
    while (atual != nullptr) {
        if (atual->valor == valor) {
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}

void removerDaLista(No* &head, int valor) {
    if (head == nullptr) {
        return;
    }
    if (head->valor == valor) {
        No* temp = head;
        head = head->proximo;
        delete temp;
        return;
    }
    No* atual = head;
    while (atual->proximo != nullptr && atual->proximo->valor != valor) {
        atual = atual->proximo;
    }
    if (atual->proximo == nullptr) {
        cout << "Valor nao encontrado!" << endl;
        return;
    }
    No* temp = atual->proximo;
    atual->proximo = temp->proximo;
    delete temp;
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
            case 3:
                imprimirReverso(head);
                cout << "NULL" << endl;
                break;
            case 4:
                int valor_anterior;
                cout << "Digite o valor apos o qual deseja inserir: ";
                cin >> valor_anterior;
                cout << "Digite o valor para inserir: ";
                cin >> valor;
                inserirApos(head, valor_anterior, valor);
                break;
            case 6:
                cout << "Digite o valor a remover: ";
                cin >> valor;
                removerDaLista(head, valor);
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