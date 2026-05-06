#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm> // Necessário para o std::sort

using namespace std;

const int NOT_FOUND = -1;

// --- PESQUISA LINEAR (Simples) ---
// Complexidade de Tempo: O(N)
template <typename Comparable>
int pesquisaLinear(const vector<Comparable> & a, const Comparable & x) {
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == x) {
            return i; 
        }
    }
    return NOT_FOUND; 
}

// --- PESQUISA BINÁRIA ---
// Complexidade de Tempo: O(log N)
// PRÉ-REQUISITO: O vetor 'a' precisa estar ORDENADO
template <typename Comparable>
int pesquisaBinaria(const vector<Comparable> & a, const Comparable & x) {
    int low = 0, high = a.size() - 1;

    while(low <= high) {
        int mid = low + (high - low) / 2; // Evita overflow em vetores gigantes

        if(a[mid] < x) {
            low = mid + 1; 
        } else if(a[mid] > x) {
            high = mid - 1; 
        } else {
            return mid; 
        }
    }
    
    return NOT_FOUND; 
}

int main() {
    int n;
    cout << "=== Teste de Estresse: Linear vs Binaria ===" << endl;
    cout << "Digite a quantidade de elementos (ex: 10000000): ";
    cin >> n;

    // 1. Criando o vetor com 'n' elementos
    vector<int> dados(n);
    
    // 2. Gerador de números aleatórios moderno do C++11
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, n * 10);

    cout << "Gerando " << n << " numeros aleatorios..." << endl;
    for (int i = 0; i < n; ++i) {
        dados[i] = dis(gen);
    }

    // 3. Ordenando o vetor
    sort(dados.begin(), dados.end());

    // 4. Vamos buscar o último elemento
    int alvo = dados.back();
    
    cout << "\nIniciando as buscas pelo alvo: " << alvo << endl;
    cout << "------------------------------------------------" << endl;

    // ==========================================
    // CRONOMETRANDO A PESQUISA LINEAR
    // ==========================================
    auto inicioLinear = chrono::high_resolution_clock::now();
    
    int idxLinear = pesquisaLinear(dados, alvo);
    
    auto fimLinear = chrono::high_resolution_clock::now();
    auto tempoLinear = chrono::duration_cast<chrono::microseconds>(fimLinear - inicioLinear).count();

    // ==========================================
    // CRONOMETRANDO A PESQUISA BINÁRIA
    // ==========================================
    auto inicioBinaria = chrono::high_resolution_clock::now();
    
    int idxBinaria = pesquisaBinaria(dados, alvo);
    
    auto fimBinaria = chrono::high_resolution_clock::now();
    auto tempoBinaria = chrono::duration_cast<chrono::microseconds>(fimBinaria - inicioBinaria).count();

    // ==========================================
    // RESULTADOS
    // ==========================================
    cout << "-> Pesquisa Linear:" << endl;
    cout << "   Encontrado no indice: " << idxLinear << endl;
    cout << "   Tempo de execucao: " << tempoLinear << " microsegundos" << endl;
    
    cout << "\n-> Pesquisa Binaria:" << endl;
    cout << "   Encontrado no indice: " << idxBinaria << endl;
    cout << "   Tempo de execucao: " << tempoBinaria << " microsegundos" << endl;
    cout << "------------------------------------------------" << endl;

    return 0;
}