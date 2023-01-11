#include "../include/ArvoreVP.h"
#include <stack>
// construtor
ArvoreVP::ArvoreVP() {
    vazio = new NoVP();
    vazio->cor = COR::BLACK;
    raiz = vazio;
}

// destructor
ArvoreVP::~ArvoreVP() {
    // desalocar memoria
}

void ArvoreVP::LeftRotate(NoVP* x) {
    NoVP *y = x->right;
    x->right = y->left;
    if (y->left != vazio)
        y->left->pai = x;
    y->pai = x->pai;
    if (x->pai == vazio)
        raiz = y;
    else if (x == x->pai->left)
        x->pai->left = y;
    else
        x->pai->right = y;
    y->left = x;
    x->pai = y;
}

void ArvoreVP::RightRotate(NoVP* x) {
    NoVP *y = x->left;
    x->left = y->right;
    if (y->right != vazio)
        y->right->pai = x;
    y->pai = x->pai;
    if (x->pai == vazio)
        raiz = y;
    else if (x == x->pai->right)
        x->pai->right = y;
    else
        x->pai->left = y;
    y->right = x;
    x->pai = y;
}

void ArvoreVP::Balanceamento_Insere(NoVP*& novp) {
    NoVP *tio;
    while (novp != raiz && novp->pai->cor == COR::RED) {
        if (novp->pai == novp->pai->pai->left) {
            tio = novp->pai->pai->right;
            if (tio->cor == COR::RED) {
                novp->pai->cor = COR::BLACK;
                tio->cor = COR::BLACK;
                novp->pai->pai->cor = COR::RED;
                novp = novp->pai->pai;
            } else {
                if (novp == novp->pai->right) {
                    novp = novp->pai;
                    LeftRotate(novp);
                }
                novp->pai->cor = COR::BLACK;
                novp->pai->pai->cor = COR::RED;
                RightRotate(novp->pai->pai);
            }
        } else {
            tio = novp->pai->pai->left;
            if (tio->cor == COR::RED) {
                novp->pai->cor = COR::BLACK;
                tio->cor = COR::BLACK;
                novp->pai->pai->cor = COR::RED;
                novp = novp->pai->pai;
            } else {
                if (novp == novp->pai->left) {
                    novp = novp->pai;
                    RightRotate(novp);
                }
                novp->pai->cor = COR::BLACK;
                novp->pai->pai->cor = COR::RED;
                LeftRotate(novp->pai->pai);
            }
        }
    }
    raiz->cor = COR::BLACK;
}


void ArvoreVP::insere(ProductReview* pr) {
    std::string valorid = pr->getUserId()+""+pr->getProductId();
    NoVP* new_novp = new NoVP(valorid, COR::RED);
    NoVP* novp = raiz;
    NoVP* pai = vazio;
    while (novp != vazio) {
        pai = novp;
        if (valorid.compare(novp->valorid) < 0)
            novp = novp->left;
        else
            novp = novp->right;
    }
    new_novp->pai = pai;
    if (pai == vazio) {
        raiz = new_novp;
        new_novp->cor = COR::BLACK;
    } else if (valorid.compare(pai->valorid) < 0) {
        pai->left = new_novp;
    } else {
        pai->right = new_novp;
    }
    Balanceamento_Insere(new_novp);
}

void ArvoreVP::insere(std::string str) {
    std::string valorid = str;
    NoVP* new_novp = new NoVP(valorid, COR::RED);
    NoVP* novp = raiz;
    NoVP* pai = vazio;
    while (novp != vazio) {
        pai = novp;
        if (valorid.compare(novp->valorid) < 0)
            novp = novp->left;
        else
            novp = novp->right;
    }
    new_novp->pai = pai;
    if (pai == vazio) {
        raiz = new_novp;
        new_novp->cor = COR::BLACK;
    } else if (valorid.compare(pai->valorid) < 0) {
        pai->left = new_novp;
    } else {
        pai->right = new_novp;
    }
    Balanceamento_Insere(new_novp);
}

ProductReview* ArvoreVP::busca(std::string userId,std::string productId){
    std::string valorid = userId + productId;
    NoVP* novp = raiz;
    ProductReview* Prod;

    while (novp != vazio) {
        if (valorid.compare(novp->valorid) == 0){ // achou o valorid
            Prod = new ProductReview(novp->getBase());
            return Prod;
        }
        else if (valorid.compare(novp->valorid) < 0) // valorid é menor
            novp = novp->left;
        else // valorid is maior
            novp = novp->right;
    }

    return nullptr; // valorid não foi encontrado
}

void ArvoreVP::print() {
    In_Ordem(raiz);
}

void ArvoreVP::In_Ordem(NoVP* raiz) {
    std::stack<NoVP*> stack;
    NoVP* no_imprime = raiz;
    while (!stack.empty() || no_imprime != vazio) {
        if (no_imprime != vazio) {
            stack.push(no_imprime);
            no_imprime = no_imprime->left;
        } else {
            no_imprime = stack.top();
            stack.pop();
            std::cout << no_imprime-> valorid << std::endl;
            no_imprime = no_imprime->right;
        }
    }
}




/*
NoVP* ArvoreVP::Search(std::string valorid) {
    NoVP* novp = raiz;
    while (novp != vazio) {
        if (valorid.compare(novp->valorid) == 0) // found the valorid
            return novp;
        else if (valorid.compare(novp->valorid) < 0) // valorid is smaller
            novp = novp->left;
        else // valorid is greater
            novp = novp->right;
    }
    return vazio; // valorid not found
}
*/