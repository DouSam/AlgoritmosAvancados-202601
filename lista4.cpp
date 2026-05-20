#include <iostream>

using namespace std;

// Estrutura do Nó da Árvore
struct BinaryNode {
    int element;
    BinaryNode *left;
    BinaryNode *right;
    
    BinaryNode(int theElement, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr)
        : element{theElement}, left{lt}, right{rt} { }
};

// Função auxiliar de inserção para montarmos a árvore de teste
void insert(int x, BinaryNode * & t) {
    if( t == nullptr ) 
        t = new BinaryNode( x, nullptr, nullptr );
    else if( x < t->element ) 
        insert( x, t->left );
    else if( t->element < x ) 
        insert( x, t->right );
}

void emOrdem(BinaryNode *t) {
    if( t != nullptr ) {
        emOrdem( t->left );        
        cout << t->element << " "; 
        emOrdem( t->right );       
    }
}

// =======================================================
// DESAFIO 1 : ESTATÍSTICAS DA ÁRVORE
// =======================================================

// 1.1 Conta todos os nós da árvore
int contarNos(BinaryNode *t) {
    if (t == nullptr) return 0;
    return 1 + contarNos(t->left) + contarNos(t->right);
}

// 1.2 Conta apenas os nós que são folhas (sem filhos)
int contarFolhas(BinaryNode *t) {
    if (t == nullptr) return 0;
    
    // Se não tem filho na esquerda nem na direita, é uma folha!
    if (t->left == nullptr && t->right == nullptr) return 1;
    
    return contarFolhas(t->left) + contarFolhas(t->right);
}

// 1.3 Conta apenas os nós "cheios" (que possuem os dois filhos)
int contarNosCheios(BinaryNode *t) {
    if (t == nullptr) return 0;
    
    // Verifica se este nó em específico possui ambos os filhos
    int cont = (t->left != nullptr && t->right != nullptr) ? 1 : 0;
    
    return cont + contarNosCheios(t->left) + contarNosCheios(t->right);
}


// =======================================================
// DESAFIO 2: BUSCA POR INTERVALO
// =======================================================
void buscaIntervalo(BinaryNode *t, int k1, int k2) {
    if (t == nullptr) return;

    if (k1 < t->element) {
        buscaIntervalo(t->left, k1, k2);
    }

    if (k1 <= t->element && t->element <= k2) {
        cout << t->element << " ";
    }

    if (t->element < k2) {
        buscaIntervalo(t->right, k1, k2);
    }
}


// =======================================================
// DESAFIO 3: A PODA DO OUTONO
// =======================================================
void podarFolhas(BinaryNode * & t) {
    if (t == nullptr) return;

    if (t->left == nullptr && t->right == nullptr) {
        delete t;
        t = nullptr;
        return;
    }

    podarFolhas(t->left);
    podarFolhas(t->right);
}

int main() {
    BinaryNode* raiz = nullptr;

    int chaves[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
    for(int k : chaves) {
        insert(k, raiz);
    }

    cout << "Arvore Original (Em-Ordem): ";
    emOrdem(raiz);
    cout << "\n\n";

    cout << "=== RESULTADOS DO DESAFIO 1 ===" << endl;
    cout << "Total de Nos: " << contarNos(raiz) << endl;
    cout << "Total de Folhas: " << contarFolhas(raiz) << endl;
    cout << "Total de Nos Cheios: " << contarNosCheios(raiz) << endl;
    cout << "---------------------------------\n" << endl;

    cout << "=== RESULTADOS DO DESAFIO 2 ===" << endl;
    int min = 35, max = 70;
    cout << "Buscando intervalo [" << min << " ate " << max << "]: ";
    buscaIntervalo(raiz, min, max);
    cout << "\n---------------------------------\n" << endl;

    cout << "=== RESULTADOS DO DESAFIO 3 ===" << endl;
    cout << "Iniciando a poda das folhas..." << endl;
    podarFolhas(raiz);
    
    cout << "Arvore Podada (Em-Ordem): ";
    emOrdem(raiz); 
    
    return 0;
}