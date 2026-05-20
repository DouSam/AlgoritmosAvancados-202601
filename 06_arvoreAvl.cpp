#include <iostream>
#include <algorithm> // Para std::max

using namespace std;

// ==========================================
// 1. ESTRUTURA DO NÓ AVL
// ==========================================
struct AvlNode {
    int element;
    AvlNode *left;
    AvlNode *right;
    int height;

    AvlNode( const int & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
      : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
};

// ==========================================
// 2. FUNÇÃO AUXILIAR DE ALTURA
// ==========================================
// Retorna a altura do nó ou -1 se for um ponteiro nulo
int height( AvlNode *t ) {
    return t == nullptr ? -1 : t->height;
}

// ==========================================
// 3. AS ROTAÇÕES
// ==========================================

void rotateWithLeftChild( AvlNode * & k2 ) {
    AvlNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    // Atualiza as alturas após o giro
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    k2 = k1; // k1 vira a nova raiz da subárvore
}

void rotateWithRightChild( AvlNode * & k1 ) {
    AvlNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
}

// Rotação Dupla (Esquerda-Direita / Caso 2)
void doubleWithLeftChild( AvlNode * & k3 ) {
    rotateWithRightChild( k3->left );
    rotateWithLeftChild( k3 );
}

// Rotação Dupla (Direita-Esquerda / Caso 3)
void doubleWithRightChild( AvlNode * & k1 ) {
    rotateWithLeftChild( k1->right );
    rotateWithRightChild( k1 );
}

// ==========================================
// 4. O ALGORITMO DE BALANCEAMENTO
// ==========================================
static const int ALLOWED_IMBALANCE = 1;

void balance( AvlNode * & t ) {
    if( t == nullptr )
        return;
        
    // Verifica se a Esquerda está mais pesada
    if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
        if( height( t->left->left ) >= height( t->left->right ) )
            rotateWithLeftChild( t );
        else
            doubleWithLeftChild( t );
    }
    // Verifica se a Direita está mais pesada
    else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
        if( height( t->right->right ) >= height( t->right->left ) )
            rotateWithRightChild( t );
        else
            doubleWithRightChild( t );
    }
    
    // Atualiza a altura do nó atual após o balanceamento
    t->height = max( height( t->left ), height( t->right ) ) + 1;
}

// ==========================================
// 5. INSERÇÃO
// ==========================================
void insert( const int & x, AvlNode * & t ) {
    if( t == nullptr )
        t = new AvlNode{ x, nullptr, nullptr };
    else if( x < t->element )
        insert( x, t->left );
    else if( t->element < x )
        insert( x, t->right );
        
    balance( t );
}

// ==========================================
// 6. EM-ORDEM PARA VER A ÁRVORE
// ==========================================
void emOrdem( AvlNode *t ) {
    if( t != nullptr ) {
        emOrdem( t->left );        
        cout << t->element << " "; 
        emOrdem( t->right );       
    }
}

int main() {
    AvlNode* raiz = nullptr;

    int chaves[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
    for(int k : chaves) {
        insert(k, raiz);
    }

    cout << "Arvore AVL (Em-Ordem): ";
    emOrdem(raiz);
    cout << "\n\n";

    return 0;
}