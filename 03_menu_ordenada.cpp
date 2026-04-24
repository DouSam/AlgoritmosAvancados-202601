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
        cout << "Menu - Lista Ordenada:" << endl;
        cout << "0. Inserir valor (Ordenado)" << endl;
        cout << "1. Imprimir lista" << endl;
        cout << "2. Buscar na lista" << endl;
        cout << "3. Remover da lista" << endl;
        cout << "4. Limpar a lista" << endl;
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