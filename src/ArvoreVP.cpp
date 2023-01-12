#include "../include/ArvoreVP.h"
#include <stack>
// construtor
ArvoreVP::ArvoreVP() {
    vazio = new NoVP();
    vazio->setcor(COR::BLACK);
    raiz = vazio;
}

// destrutor
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
    while (novp != raiz && novp->pai->getcor() == COR::RED) {
        if (novp->pai == novp->pai->pai->left) {
            tio = novp->pai->pai->right;
            if (tio->getcor() == COR::RED) {
                novp->pai->setcor(COR::BLACK);
                tio->setcor(COR::BLACK);
                novp->pai->pai->setcor(COR::RED);
                novp = novp->pai->pai;
            } else {
                if (novp == novp->pai->right) {
                    novp = novp->pai;
                    LeftRotate(novp);
                }
                novp->pai->setcor(COR::BLACK);
                novp->pai->pai->setcor(COR::RED);
                RightRotate(novp->pai->pai);
            }
        } else {
            tio = novp->pai->pai->left;
            if (tio->getcor() == COR::RED) {
                novp->pai->setcor(COR::BLACK);
                tio->setcor(COR::BLACK);
                novp->pai->pai->setcor(COR::RED);
                novp = novp->pai->pai;
            } else {
                if (novp == novp->pai->left) {
                    novp = novp->pai;
                    RightRotate(novp);
                }
                novp->pai->setcor(COR::BLACK);
                novp->pai->pai->setcor(COR::RED);
                LeftRotate(novp->pai->pai);
            }
        }
    }
    raiz->setcor(COR::BLACK);
}

/*
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
*/
void ArvoreVP::insere(ProductReview* pr) {
    std::string valorid2 = pr->getUserId()+""+pr->getProductId();
    NoVP* new_novp = new NoVP(valorid2, COR::RED);
    NoVP* novp_x = raiz;
    NoVP* novp_y = vazio;
    while (novp_x != vazio){
        novp_y = novp_x;
        if (new_novp->getId() < novp_x->getId()) {
            novp_x = novp_x->left;
        } else {
            novp_x = novp_x->right;
        }
    }
    new_novp->pai = novp_y;
    if (novp_y == vazio) {
        raiz = new_novp;
    } else if (new_novp->getId() < novp_y->getId()) {
        novp_y->left = new_novp;
    } else {
        novp_y->right = new_novp;
    }
    new_novp->left = vazio;
    new_novp->right = vazio;
    Balanceamento_Insere(new_novp);
}

void ArvoreVP::insere(std::string valorid2) {
    NoVP* new_novp = new NoVP(valorid2, COR::RED);
    NoVP* novp_x = raiz;
    NoVP* novp_y = vazio;
    while (novp_x != vazio) {
        novp_y = novp_x;
        if (new_novp->getId() < novp_x->getId()) {
            novp_x = novp_x->left;
        } else {
            novp_x = novp_x->right;
        }
    }
    new_novp->pai = novp_y;
    if (novp_y == vazio) {
        raiz = new_novp;
    } else if (new_novp->getId() < novp_y->getId()) {
        novp_y->left = new_novp;
    } else {
        novp_y->right = new_novp;
    }
    new_novp->left = vazio;
    new_novp->right = vazio;
    Balanceamento_Insere(new_novp);
}
/*
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
        else // valorid é maior
            novp = novp->right;
    }

    return nullptr; // valorid não foi encontrado
}
*/
ProductReview* ArvoreVP::busca(std::string userId,std::string productId){
    std::string valorid = userId + productId;
    NoVP* novp = raiz;
    ProductReview* Prod;
    while (novp != vazio) {
        if (novp->getId() == valorid) {  // achou o valorid
            Prod = new ProductReview(novp->getBase());
            return Prod;
        } else if (valorid < novp->getId()) { // valorid é menor
            novp = novp->left;
        } else {  // valorid é maior
            novp = novp->right;
        }
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
            std::cout << no_imprime->getId() << std::endl;
            no_imprime = no_imprime->right;
        }
    }
}




/*
NoVP* ArvoreVP::Search(std::string valorid) {
    NoVP* novp = raiz;
    while (novp != vazio) {
        if (valorid.compare(novp->valorid) == 0) // achou o valorid
            return novp;
        else if (valorid.compare(novp->valorid) < 0) // valorid é menor
            novp = novp->left;
        else // valorid é maior
            novp = novp->right;
    }
    return vazio; // valorid não foi encontrado
}
*/