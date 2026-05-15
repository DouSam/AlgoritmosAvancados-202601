#include <iostream>
#include <clocale>

using namespace std;

// 1. A Estrutura do Nó Binário
struct BinaryNode {
    int value;              // O dado armazenado
    BinaryNode *left;       // Ponteiro para o filho da Esquerda
    BinaryNode *right;      // Ponteiro para o filho da Direita
    
    // Construtor para facilitar a alocação de memória no Heap
    BinaryNode(int theValue, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr)
        : value{theValue}, left{lt}, right{rt} { }
};

// 2. A Inserção Recursiva 
void insert(int x, BinaryNode * & t) {
    if( t == nullptr ) {
        // Encontrou um espaço vazio! O nó pai agora aponta para este novo nó
        t = new BinaryNode( x, nullptr, nullptr );
    } 
    else if( x < t->value ) {
        // Se o valor é menor, desce para a esquerda
        insert( x, t->left );
    } 
    else if( t->value < x ) {
        // Se o valor é maior, desce para a direita
        insert( x, t->right );
    } 
    else {
        // Valor duplicado: a convenção comum é não fazer nada
        ; 
    }
}

// 1. PRÉ-ORDEM (Preorder): Nó -> Esquerda -> Direita
void preOrdem(BinaryNode *t) {
    if( t != nullptr ) {
        cout << t->value << " "; 
        preOrdem( t->left );       
        preOrdem( t->right );      
    }
}

// 2. EM-ORDEM (Inorder): Esquerda -> Nó -> Direita
void emOrdem(BinaryNode *t) {
    if( t != nullptr ) {
        emOrdem( t->left );        
        cout << t->value << " "; 
        emOrdem( t->right );       
    }
}

// 3. PÓS-ORDEM (Postorder): Esquerda -> Direita -> Nó
void posOrdem(BinaryNode *t) {
    if( t != nullptr ) {
        posOrdem( t->left );       
        posOrdem( t->right );      
        cout << t->value << " ";
    }
}

// ==========================================
// 1. CONTAINS (Busca)
// ==========================================
bool contains(const int & x, BinaryNode *t) {
    if( t == nullptr ) 
        return false; // Chegou ao fim e não achou
    else if( x < t->value ) 
        return contains( x, t->left );  // O alvo é menor, vai para a esquerda
    else if( t->value < x ) 
        return contains( x, t->right ); // O alvo é maior, vai para a direita
    else 
        return true; // Match! Encontrou o valor
}

// ==========================================
// 2. FIND MIN (Menor valor - Recursivo)
// ==========================================
BinaryNode* findMin(BinaryNode *t) {
    if( t == nullptr ) 
        return nullptr;
    if( t->left == nullptr ) 
        return t; // Achou o nó mais à esquerda
    
    return findMin( t->left );
}

// ==========================================
// 3. FIND MAX (Maior valor - Iterativo)
// ==========================================
BinaryNode* findMax(BinaryNode *t)  {
    if( t != nullptr ) {
        while( t->right != nullptr ) {
            t = t->right; // Desce tudo para a direita
        }
    }
    return t;
}

// ==========================================
// 4. REMOVE (Exclusão de um nó)
// ==========================================
// Recebe o ponteiro por referência (* &t) para poder alterar a árvore
void remove(const int & x, BinaryNode * & t) {
    if( t == nullptr ) 
        return; // Item não encontrado; não faz nada
        
    if( x < t->value ) {
        remove( x, t->left );
    } 
    else if( t->value < x ) {
        remove( x, t->right );
    } 
    else if( t->left != nullptr && t->right != nullptr ) { 
        // CASO 3: O nó tem dois filhos
        t->value = findMin( t->right )->value;   // Substitui pelo menor da direita
        remove( t->value, t->right );            // Remove o nó substituto lá embaixo
    } 
    else { 
        // CASOS 1 e 2: O nó tem um filho ou é uma folha (nenhum filho)
        BinaryNode *oldNode = t;
        t = ( t->left != nullptr ) ? t->left : t->right; // Pula o nó a ser deletado
        delete oldNode; // Limpa o Heap
    }
}

void cleanTree(BinaryNode * & t) {
    if (t != nullptr) {
        cleanTree(t->left);
        cleanTree(t->right);
        delete t;
        t = nullptr;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    BinaryNode* raiz = nullptr; // Inicializa a árvore vazia
    
    insert(50, raiz);
    insert(25, raiz);
    insert(30, raiz);
    insert(20, raiz);
    insert(60, raiz);
    insert(55, raiz);
    insert(70, raiz);
    insert(80, raiz);
    
    cout << "Arvore impressa Em-Ordem:" << endl;
    emOrdem(raiz);
    cout << endl;

    cout << "Arvore impressa Pré-Ordem:" << endl;
    preOrdem(raiz);
    cout << endl;

    cout << "Arvore impressa Pós-Ordem:" << endl;
    posOrdem(raiz);
    cout << endl;
    
    BinaryNode *maxNo = findMax(raiz);

    cout << "Maior valor: " << maxNo->value << endl;
    cout << "Menor valor: " << findMin(raiz)->value << endl;

    cout << "Removendo 70..." << endl;
    remove(70, raiz);

    cout << "Arvore impressa Em-Ordem após remoção:" << endl;
    emOrdem(raiz);
    cout << endl;

    remove(25, raiz);
    cout << "Arvore impressa Em-Ordem após remoção de 25:" << endl;
    emOrdem(raiz);
    cout << endl;

    cleanTree(raiz);
    cout << "Lista limpa: ";
    emOrdem(raiz);
    
    return 0;
}