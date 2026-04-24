#include <iostream>
using namespace std;

struct No {
    int valor;
    No *proximo;
};

int main() {
    No* head = nullptr;
    
    int opcao, valor;
    do {
        cout << "Menu - Pilha (Stack):" << endl;
        cout << "0. Empilhar (Push)" << endl;
        cout << "1. Desempilhar (Pop)" << endl;
        cout << "2. Consultar o Topo (Top)" << endl;
        cout << "3. Verificar se esta vazia" << endl;
        cout << "4. Limpar a pilha" << endl;
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