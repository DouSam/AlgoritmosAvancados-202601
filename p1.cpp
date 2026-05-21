/* Máquina de venda automática:
   - Modos: Usuário (padrão) e Administrador (senha: "senha123")
   - Estruturas usadas: Fila, Pilha, Lista Duplamente Encadeada, alocação dinâmica (new/delete)
   - Ordenação: insertion sort
   - Funcionalidades: listar, comprar, cadastrar, repor, relatórios de faturamento
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Produto
{
    int id;
    string nome;
    double preco;
    int qtde;
};

struct No
{
    Produto *p;
    No *prev;
    No *next;
    No(Produto *prod) : p(prod), prev(nullptr), next(nullptr) {}
};

struct ListaProdutos
{
    No *head;
    No *tail;
    int nextId;

    ListaProdutos() : head(new No(nullptr)), tail(new No(nullptr)), nextId(1)
    {
        head->next = tail;
        tail->prev = head;
    }

    ~ListaProdutos()
    {
        No *cur = head->next;
        while (cur != tail)
        {
            No *prox = cur->next;
            delete cur->p;
            delete cur;
            cur = prox;
        }
        delete head;
        delete tail;
    }

    Produto *adicionar(const string &nome, double preco, int qtde)
    {
        Produto *prod = new Produto{nextId++, nome, preco, qtde};
        No *n = new No(prod);
        n->prev = tail->prev;
        n->next = tail;
        tail->prev->next = n;
        tail->prev = n;
        return prod;
    }

    No *buscarPorId(int id)
    {
        No *cur = head->next;
        while (cur != tail)
        {
            if (cur->p->id == id)
                return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    bool vazia() const
    {
        return head->next == tail;
    }

    ListaProdutos *copiarOrdenadoInsertion(bool porQtde)
    {
        ListaProdutos *copia = new ListaProdutos();
        for (No *cur = head->next; cur != tail; cur = cur->next)
        {
            Produto *novoProduto = new Produto{cur->p->id, cur->p->nome, cur->p->preco, cur->p->qtde};
            No *novoNo = new No(novoProduto);

            No *pos = copia->head->next;
            while (pos != copia->tail)
            {
                bool entraAntes = porQtde ? (novoProduto->qtde > pos->p->qtde)
                                          : (novoProduto->preco > pos->p->preco);
                if (entraAntes)
                    break;
                pos = pos->next;
            }

            novoNo->next = pos;
            novoNo->prev = pos->prev;
            pos->prev->next = novoNo;
            pos->prev = novoNo;
        }
        return copia;
    }
};

struct NoPilha
{
    string nome;
    NoPilha *prox;
    NoPilha(const string &n) : nome(n), prox(nullptr) {}
};

struct PilhaHistorico
{
    NoPilha *topo;
    PilhaHistorico() : topo(nullptr) {}

    ~PilhaHistorico()
    {
        while (topo)
        {
            NoPilha *t = topo->prox;
            delete topo;
            topo = t;
        }
    }

    void push(const string &s)
    {
        NoPilha *n = new NoPilha(s);
        n->prox = topo;
        topo = n;
    }

    bool vazia() const { return topo == nullptr; }

    string pop()
    {
        if (!topo)
            return string("");
        string s = topo->nome;
        NoPilha *t = topo;
        topo = topo->prox;
        delete t;
        return s;
    }
};

struct Venda
{
    int id;
    string nome;
    double pago;
    double preco;
};

struct NoFilaVenda
{
    Venda dado;
    NoFilaVenda *prox;
    NoFilaVenda(const Venda &v) : dado(v), prox(nullptr) {}
};

struct FilaVendas
{
    NoFilaVenda *inicio;
    NoFilaVenda *fim;

    FilaVendas() : inicio(nullptr), fim(nullptr) {}

    ~FilaVendas()
    {
        while (inicio)
        {
            NoFilaVenda *t = inicio->prox;
            delete inicio;
            inicio = t;
        }
        fim = nullptr;
    }

    void enfileirar(const Venda &v)
    {
        NoFilaVenda *n = new NoFilaVenda(v);
        if (!fim)
        {
            inicio = fim = n;
        }
        else
        {
            fim->prox = n;
            fim = n;
        }
    }

    bool vazia() const { return inicio == nullptr; }
};

void descartarLinha()
{
    int c;
    while ((c = cin.get()) != EOF && c != '\n')
    {
    }
}

void limparTela()
{
    system("cls");
}

void clearCin()
{
    cin.clear();
    descartarLinha();
}

ListaProdutos produtos;
PilhaHistorico historico;
FilaVendas filaVendas;
double faturamentoTotal = 0.0;

void imprimirLista(const ListaProdutos &lst)
{
    cout << left << setw(6) << "ID" << setw(25) << "Produto" << setw(10) << "Preco" << setw(8) << "Qtde" << '\n';
    cout << string(55, '-') << '\n';
    No *cur = lst.head->next;
    while (cur != lst.tail)
    {
        cout << setw(6) << cur->p->id << setw(25) << cur->p->nome << fixed << setprecision(2)
             << setw(10) << cur->p->preco << setw(8) << cur->p->qtde << '\n';
        cur = cur->next;
    }
}

void listarProdutos()
{
    imprimirLista(produtos);
}

void listarOrdenadoPorQtdeOuPreco(bool porQtde)
{
    if (produtos.vazia())
    {
        cout << "Nao ha produtos." << '\n';
        return;
    }

    ListaProdutos *copia = produtos.copiarOrdenadoInsertion(porQtde);
    cout << (porQtde ? "Ordenado por quantidade (desc)" : "Ordenado por preco (desc)") << '\n';
    imprimirLista(*copia);
    delete copia;
}

double valorEstoque()
{
    double soma = 0.0;
    No *cur = produtos.head->next;
    while (cur != produtos.tail)
    {
        soma += cur->p->preco * cur->p->qtde;
        cur = cur->next;
    }
    return soma;
}

void comprarUsuario()
{
    listarProdutos();
    cout << "Digite o ID do produto que deseja comprar (0 para voltar): ";
    int id;
    if (!(cin >> id))
    {
        clearCin();
        return;
    }
    if (id == 0)
        return;

    No *n = produtos.buscarPorId(id);
    if (!n)
    {
        cout << "Produto nao encontrado." << '\n';
        return;
    }
    if (n->p->qtde <= 0)
    {
        cout << "Produto sem estoque." << '\n';
        return;
    }

    cout << "Preco: R$ " << fixed << setprecision(2) << n->p->preco << ". Insira o valor: R$ ";
    double pago;
    if (!(cin >> pago))
    {
        clearCin();
        return;
    }
    if (pago < n->p->preco)
    {
        cout << "Valor insuficiente. Compra cancelada." << '\n';
        return;
    }

    double troco = pago - n->p->preco;
    n->p->qtde -= 1;
    faturamentoTotal += n->p->preco;
    historico.push(n->p->nome);
    filaVendas.enfileirar(Venda{n->p->id, n->p->nome, pago, n->p->preco});

    cout << "Dispensando: " << n->p->nome << " | Troco: R$ " << fixed << setprecision(2) << troco << '\n';
}

void adminCadastrar()
{
    cout << "Nome do produto: ";
    clearCin();
    string nome;
    getline(cin, nome);

    cout << "Preco: ";
    double preco;
    if (!(cin >> preco))
    {
        clearCin();
        cout << "Preco invalido." << '\n';
        return;
    }

    cout << "Quantidade inicial: ";
    int qt;
    if (!(cin >> qt))
    {
        clearCin();
        cout << "Quantidade invalida." << '\n';
        return;
    }

    Produto *p = produtos.adicionar(nome, preco, qt);
    cout << "Produto cadastrado com ID " << p->id << '\n';
}

void adminRepor()
{
    listarProdutos();
    cout << "Digite o ID do produto para repor (0 para voltar): ";
    int id;
    if (!(cin >> id))
    {
        clearCin();
        return;
    }
    if (id == 0)
        return;

    No *n = produtos.buscarPorId(id);
    if (!n)
    {
        cout << "Produto nao encontrado." << '\n';
        return;
    }

    cout << "Quantidade a adicionar: ";
    int add;
    if (!(cin >> add))
    {
        clearCin();
        return;
    }

    n->p->qtde += add;
    cout << "Novo estoque de " << n->p->nome << ": " << n->p->qtde << '\n';
}

void adminRelatorios()
{
    cout << "Faturamento total: R$ " << fixed << setprecision(2) << faturamentoTotal << '\n';
    cout << "Valor total em estoque (faturamento previsto): R$ " << fixed << setprecision(2) << valorEstoque() << '\n';
    cout << "Ultimas vendas:" << '\n';

    NoFilaVenda *cur = filaVendas.inicio;
    while (cur)
    {
        cout << " - " << cur->dado.nome << ": pago R$ " << fixed << setprecision(2) << cur->dado.pago
             << " (preco " << cur->dado.preco << ")" << '\n';
        cur = cur->prox;
    }
}

void menuAdministrador()
{
    while (true)
    {
        cout << "--- Modo Administrador ---\n";
        cout << "1. Cadastrar novo produto\n2. Repor produto\n3. Listar inventario por quantidade\n4. Listar inventario por preco\n5. Relatorios (faturamento)\n6. Voltar\nEscolha: ";
        int op;
        if (!(cin >> op))
        {
            clearCin();
            return;
        }
        limparTela();

        switch (op)
        {
        case 1:
            adminCadastrar();
            break;
        case 2:
            adminRepor();
            break;
        case 3:
            listarOrdenadoPorQtdeOuPreco(true);
            break;
        case 4:
            listarOrdenadoPorQtdeOuPreco(false);
            break;
        case 5:
            adminRelatorios();
            break;
        case 6:
            return;
        default:
            cout << "Opcao invalida." << '\n';
            break;
        }
    }
}

int main()
{
    produtos.adicionar("Agua 500ml", 3.50, 10);
    produtos.adicionar("Refrigerante 350ml", 5.00, 8);
    produtos.adicionar("Sanduiche", 8.75, 5);
    produtos.adicionar("Biscoito", 2.25, 20);

    while (true)
    {
        cout << "--- Maquina de Venda Automatica ---\n";
        cout << "1. Modo Usuario\n2. Modo Administrador\n3. Historico de dispensas\n4. Sair\nEscolha: ";
        int op;
        if (!(cin >> op))
        {
            clearCin();
            break;
        }
        limparTela();
        switch (op)
        {
        case 1:
            comprarUsuario();
            break;
        case 2:
        {
            cout << "Senha: ";
            string pass;
            clearCin();
            getline(cin, pass);
            if (pass == "senha123")
                menuAdministrador();
            else
            {
                cout << "Senha incorreta." << '\n';
            }
            break;
        }
        case 3:
        {
            cout << "Historico\n";
            while (!historico.vazia())
                cout << " - " << historico.pop() << '\n';
            break;
        }
        case 4:
            cout << "Encerrando...\n";
            return 0;
        default:
            cout << "Opcao invalida." << '\n';
            break;
        }
    }

    return 0;
}
