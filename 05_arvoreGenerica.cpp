#include <iostream>
#include <string>
#include <clocale>

using namespace std;

struct TreeNode { 
    string element;          // Valor (int, string, ou um Object)
    TreeNode *firstChild;    
    TreeNode *nextSibling;   
};

void imprimirArvore(TreeNode* no, int profundidade = 0) {
    if (no == nullptr) return;

    for (int i = 0; i < profundidade; ++i) {
        cout << "   "; 
    }
    cout << "- " << no->element << endl;

    TreeNode* filhoAtual = no->firstChild;
    
    while (filhoAtual != nullptr) {
        imprimirArvore(filhoAtual, profundidade + 1);
        
        filhoAtual = filhoAtual->nextSibling;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    TreeNode* raiz = new TreeNode{"/usr", nullptr, nullptr};
    
    TreeNode* jose = new TreeNode{"jose", nullptr, nullptr};
    TreeNode* gustavo = new TreeNode{"gustavo", nullptr, nullptr};
    TreeNode* lineu = new TreeNode{"lineu", nullptr, nullptr};
    
    TreeNode* financeiro = new TreeNode{"financeiro", nullptr, nullptr};
    TreeNode* contabil = new TreeNode{"contabil", nullptr, nullptr};
    
    // Conectando a árvore (Primeiro Filho / Próximo Irmão)
    raiz->firstChild = jose;       // 'jose' é o primeiro filho de '/usr'
    jose->nextSibling = gustavo;      // 'gustavo' é irmão de 'jose'
    gustavo->nextSibling = lineu;      // 'lineu' é irmão de 'gustavo'
    
    // Adicionando filhos dentro de 'jose'
    jose->firstChild = financeiro;       // 'financeiro' é o primeiro filho de 'jose'
    financeiro->nextSibling = contabil;    // 'contabil' é irmão de 'financeiro'
    
    // Percorrendo a árvore
    cout << "Estrutura de Diretorios:" << endl;
    imprimirArvore(raiz);
    
    return 0;
}