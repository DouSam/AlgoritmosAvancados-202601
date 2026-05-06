#include <iostream>
#include <algorithm> // Para usar std::swap
#include <chrono>
#include <random>
#include <vector>

using namespace std;

struct NoDuplo {
    int valor;
    NoDuplo* anterior;
    NoDuplo* proximo;
};

// ==========================================
// 1. BUBBLE SORT (O(n^2))
// ==========================================
// Empurra o maior valor para o final da lista a cada iteração.
void bubbleSort(NoDuplo* head) {
    if (head == nullptr) return;
    
    bool trocou;
    NoDuplo* atual;
    NoDuplo* fim = nullptr; // Marca até onde precisamos ir
    
    do {
        trocou = false;
        atual = head;
        
        while (atual->proximo != fim) {
            if (atual->valor > atual->proximo->valor) {
                std::swap(atual->valor, atual->proximo->valor);
                trocou = true;
            }
            atual = atual->proximo;
        }
        fim = atual; // O último elemento já está no lugar certo
    } while (trocou);
}

// ==========================================
// 2. SELECTION SORT (O(n^2))
// ==========================================
// Procura o menor elemento do resto da lista e o traz para a posição atual.
void selectionSort(NoDuplo* head) {
    if (head == nullptr) return;
    
    NoDuplo* atual = head;
    
    while (atual != nullptr) {
        NoDuplo* minNode = atual;
        NoDuplo* iterador = atual->proximo;
        
        // Encontra o menor nó à direita do atual
        while (iterador != nullptr) {
            if (iterador->valor < minNode->valor) {
                minNode = iterador;
            }
            iterador = iterador->proximo;
        }
        
        // Se o menor não for o atual, troca os valores
        if (minNode != atual) {
            std::swap(atual->valor, minNode->valor);
        }
        
        atual = atual->proximo;
    }
}

// ==========================================
// 3. INSERTION SORT (O(n^2), O(n) no melhor caso)
// ==========================================
// Pega o nó atual e o arrasta para trás (usando o ponteiro anterior) 
// até encontrar o seu lugar correto entre os já ordenados.
void insertionSort(NoDuplo* head) {
    if (head == nullptr || head->proximo == nullptr) return;
    
    NoDuplo* atual = head->proximo;
    
    while (atual != nullptr) {
        int tempValor = atual->valor;
        NoDuplo* j = atual->anterior;
        
        // Desloca os valores maiores que tempValor para a frente
        while (j != nullptr && j->valor > tempValor) {
            j->proximo->valor = j->valor;
            j = j->anterior;
        }
        
        // Insere o valor na posição correta
        if (j == nullptr) {
            head->valor = tempValor; // Chegou no início
        } else {
            j->proximo->valor = tempValor;
        }
        
        atual = atual->proximo;
    }
}

// ==========================================
// 4. QUICKSORT (O(n log n) em média)
// ==========================================
// Como não temos acesso aleatório de trás para frente e frente para trás
// simultaneamente com facilidade matemática, usamos o esquema de partição de Lomuto,
// iterando em um único sentido.

// Função auxiliar: Particiona a lista em torno de um pivô (o último elemento)
NoDuplo* partition(NoDuplo* left, NoDuplo* right) {
    int pivot = right->valor;
    NoDuplo* i = left->anterior;
    
    for (NoDuplo* j = left; j != right; j = j->proximo) {
        if (j->valor <= pivot) {
            i = (i == nullptr) ? left : i->proximo;
            std::swap(i->valor, j->valor);
        }
    }
    
    i = (i == nullptr) ? left : i->proximo;
    std::swap(i->valor, right->valor);
    return i;
}

// Função auxiliar: Chamada recursiva do Quicksort
void quickSortRecursivo(NoDuplo* left, NoDuplo* right) {
    if (right != nullptr && left != right && left != right->proximo) {
        NoDuplo* p = partition(left, right);
        quickSortRecursivo(left, p->anterior);
        quickSortRecursivo(p->proximo, right);
    }
}

// Função principal de chamada do Quicksort
void quickSort(NoDuplo* head) {
    if (head == nullptr) return;
    
    // Primeiro, precisamos encontrar o último nó (tail)
    NoDuplo* tail = head;
    while (tail->proximo != nullptr) {
        tail = tail->proximo;
    }
    
    quickSortRecursivo(head, tail);
}

// --- FUNÇÕES AUXILIARES PARA A LISTA ---

// Insere um novo nó no fim da lista
void inserirFim(NoDuplo*& head, NoDuplo*& tail, int v) {
    NoDuplo* novo = new NoDuplo();
    novo->valor = v;
    novo->proximo = nullptr;
    novo->anterior = tail;
    
    if (tail != nullptr) {
        tail->proximo = novo;
    } else {
        head = novo; // Se a lista estava vazia
    }
    tail = novo;
}

// Limpa toda a lista do Heap para não faltar memória
void limparLista(NoDuplo*& head, NoDuplo*& tail) {
    NoDuplo* atual = head;
    while (atual != nullptr) {
        NoDuplo* temp = atual;
        atual = atual->proximo;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
}

// ==========================================
// FUNÇÃO MAIN - O BENCHMARK
// ==========================================
int main() {
    int n;
    cout << "=== Benchmarking: Ordenacao em Lista Duplamente Encadeada ===" << endl;
    cout << "Digite a quantidade de elementos (ex: 5000): ";
    cin >> n;

    // Gerador de números aleatórios moderno (C++11)
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, n * 10);

    // Guardamos os números originais em um vetor simples 
    // apenas para garantir que todas as listas testem os MESMOS dados
    vector<int> dados_originais(n);
    for(int i = 0; i < n; ++i) {
        dados_originais[i] = dis(gen);
    }

    NoDuplo *head = nullptr, *tail = nullptr;

    cout << "\nIniciando testes com N = " << n << "...\n" << endl;

    // ----------------------------------------------------
    // TESTE 1: BUBBLE SORT
    // ----------------------------------------------------
    for(int v : dados_originais) inserirFim(head, tail, v);
    auto inicio = chrono::high_resolution_clock::now();
    
    bubbleSort(head);
    
    auto fim = chrono::high_resolution_clock::now();
    cout << "-> Bubble Sort:    " 
         << chrono::duration_cast<chrono::milliseconds>(fim - inicio).count() 
         << " ms" << endl;
    limparLista(head, tail);

    // ----------------------------------------------------
    // TESTE 2: SELECTION SORT
    // ----------------------------------------------------
    for(int v : dados_originais) inserirFim(head, tail, v);
    inicio = chrono::high_resolution_clock::now();
    
    selectionSort(head);
    
    fim = chrono::high_resolution_clock::now();
    cout << "-> Selection Sort: " 
         << chrono::duration_cast<chrono::milliseconds>(fim - inicio).count() 
         << " ms" << endl;
    limparLista(head, tail);

    // ----------------------------------------------------
    // TESTE 3: INSERTION SORT
    // ----------------------------------------------------
    for(int v : dados_originais) inserirFim(head, tail, v);
    inicio = chrono::high_resolution_clock::now();
    
    insertionSort(head);
    
    fim = chrono::high_resolution_clock::now();
    cout << "-> Insertion Sort: " 
         << chrono::duration_cast<chrono::milliseconds>(fim - inicio).count() 
         << " ms" << endl;
    limparLista(head, tail);

    // ----------------------------------------------------
    // TESTE 4: QUICKSORT
    // ----------------------------------------------------
    for(int v : dados_originais) inserirFim(head, tail, v);
    inicio = chrono::high_resolution_clock::now();
    
    quickSort(head);
    
    fim = chrono::high_resolution_clock::now();
    cout << "-> Quicksort:      " 
         << chrono::duration_cast<chrono::milliseconds>(fim - inicio).count() 
         << " ms" << endl;
    limparLista(head, tail);

    return 0;
}