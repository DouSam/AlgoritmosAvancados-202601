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
        cout << "Menu - Fila (Queue):" << endl;
        cout << "0. Enfileirar (Enqueue)" << endl;
        cout << "1. Desenfileirar (Dequeue)" << endl;
        cout << "2. Consultar o primeiro da fila (Front)" << endl;
        cout << "3. Verificar se esta vazia" << endl;
        cout << "4. Limpar a fila" << endl;
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