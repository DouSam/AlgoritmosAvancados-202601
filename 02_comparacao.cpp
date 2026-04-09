#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct No {
    int valor;
    No *proximo;
};

int main() {
    const int TOTAL_ITENS = 100000;

    vector<int> meuVetor;
    auto inicioArray = high_resolution_clock::now();

    for (int i = 0; i < TOTAL_ITENS; i++) {
        // insert(begin) força o array a empurrar todos os itens 
        meuVetor.insert(meuVetor.begin(), i);
    }

    auto fimArray = high_resolution_clock::now();
    auto duracaoArray = duration_cast<milliseconds>(fimArray - inicioArray);

    // --- TESTE COM LISTA ENCADEADA ---
    No* cabeca = nullptr;
    auto inicioLista = high_resolution_clock::now();

    for (int i = 0; i < TOTAL_ITENS; i++) {
        // Inserção no início da lista: apenas muda ponteiros 
        No* novo = new No(); 
        novo->valor = i;
        novo->proximo = cabeca;
        cabeca = novo;
    }

    auto fimLista = high_resolution_clock::now();
    auto duracaoLista = duration_cast<milliseconds>(fimLista - inicioLista);

    cout << "Tempo no Array (Vetor): " << duracaoArray.count() << " ms" << endl;
    cout << "Tempo na Lista Encadeada: " << duracaoLista.count() << " ms" << endl;

    return 0;
}