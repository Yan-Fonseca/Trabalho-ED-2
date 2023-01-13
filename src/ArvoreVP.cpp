#include "../include/ArvoreVP.h"
#include <stack>
#include <algorithm>
// construtor
ArvoreVP::ArvoreVP() {
    vazio = new NoVP();
    vazio->setCor(COR::BLACK);
    raiz = vazio;
}

// destrutor
ArvoreVP::~ArvoreVP() {
    // desalocar memoria
}



void ArvoreVP::LeftRotate(NoVP* novp) {
    NoVP* aux = novp->getRight();
    novp->setRight(aux->getLeft());
    if (aux->getLeft() != vazio) {
        aux->getLeft()->setPai(novp);
    }
    aux->setPai(novp->getPai());
    if (novp->getPai() == vazio) {
        raiz = aux;
    } else if (novp == novp->getPai()->getLeft()) {
        novp->getPai()->setLeft(aux);
    } else {
        novp->getPai()->setRight(aux);
    }
    aux->setLeft(novp);
    novp->setPai(aux);
}

void ArvoreVP::RightRotate(NoVP* novp) {
    NoVP* aux = novp->getLeft();
    novp->setLeft(aux->getRight());
    if (aux->getRight() != vazio) {
        aux->getRight()->setPai(novp);
    }
    aux->setPai(novp->getPai());
    if (novp->getPai() == vazio) {
        raiz = aux;
    } else if (novp == novp->getPai()->getRight()) {
        novp->getPai()->setRight(aux);
    } else {
        novp->getPai()->setLeft(aux);
    }
    aux->setRight(novp);
    novp->setPai(aux);
}

void ArvoreVP::Balanceamento_Insere(NoVP*& novp) {
    NoVP* tio;
    while (novp != raiz && novp->getPai()->getCor() == COR::RED) {
        if (novp->getPai() == novp->getPai()->getPai()->getLeft()) {
            tio = novp->getPai()->getPai()->getRight();
            if (tio->getCor() == COR::RED) {
                novp->getPai()->setCor(COR::BLACK);
                tio->setCor(COR::BLACK);
                novp->getPai()->getPai()->setCor(COR::RED);
                novp = novp->getPai()->getPai();
            } else {
                if (novp == novp->getPai()->getRight()) {
                    novp = novp->getPai();
                    LeftRotate(novp);
                }
                novp->getPai()->setCor(COR::BLACK);
                novp->getPai()->getPai()->setCor(COR::RED);
                RightRotate(novp->getPai()->getPai());
            }
        } else {
            tio = novp->getPai()->getPai()->getLeft();
            if (tio->getCor() == COR::RED) {
                novp->getPai()->setCor(COR::BLACK);
                tio->setCor(COR::BLACK);
                novp->getPai()->getPai()->setCor(COR::RED);
                novp = novp->getPai()->getPai();
            } else {
                if (novp == novp->getPai()->getLeft()) {
                    novp = novp->getPai();
                    RightRotate(novp);
                }
                novp->getPai()->setCor(COR::BLACK);
                novp->getPai()->getPai()->setCor(COR::RED);
                LeftRotate(novp->getPai()->getPai());
            }
        }
    }
    raiz->setCor(COR::BLACK);
}


void ArvoreVP::insere(ProductReview* pr) {
    std::string valorid2 = pr->getUserId()+pr->getProductId();
    std::cout<<"valorid2 antes: "<<valorid2;
    valorid2.erase(std::remove_if(valorid2.begin(), valorid2.end(), ' '), valorid2.end());
    std::cout<<"valorid2: "<<valorid2<<"espa";
    NoVP* new_novp = new NoVP(valorid2, COR::RED, pr);
    NoVP* novp_x = raiz;
    NoVP* novp_y = vazio;
    while (novp_x != vazio) {
        novp_y = novp_x;
        if (new_novp->getId() < novp_x->getId()) {
            novp_x = novp_x->getLeft();
        } else {
            novp_x = novp_x->getRight();
        }
    }
    new_novp->setPai(novp_y);
    if (novp_y == vazio) {
        raiz = new_novp;
    } else if (new_novp->getId() < novp_y->getId()) {
        novp_y->setLeft(new_novp);
    } else {
        novp_y->setRight(new_novp);
    }
    new_novp->setLeft(vazio);
    new_novp->setRight(vazio);
    Balanceamento_Insere(new_novp);
}


ProductReview* ArvoreVP::busca(std::string userId,std::string productId) {
    std::cout<<"\n user: " << userId << "  prod: " << productId<<"\n";
    std::cout<<"sssss ";
    ProductReview* Prod;
    std::string valorid = userId + productId;
    valorid.erase(std::remove_if(valorid.begin(), valorid.end(), ' '), valorid.end());
    std::cout<<"\n valorid: " << valorid;
    NoVP* novp = raiz;
    while (novp != vazio) {
        std::cout<<"entro ";
        std::cout<<"novp->getId():"<< novp->getId();
        if (novp->getId() == valorid) {
            std::cout<<"aaaaa ";
            Prod = new ProductReview(novp->getBase());
            std::cout<<"bbbb ";
            return Prod;
            std::cout<<"cccc ";
        } else if (valorid < novp->getId()) {
            novp = novp->getLeft();
        } else {
            novp = novp->getRight();
        }
        std::cout<<"saiu ";
    }
    std::cout<<"aff ";
    return nullptr;
}

void ArvoreVP::print() {
    In_Ordem(raiz);
}
void ArvoreVP::In_Ordem(NoVP* no_imprime) {
    if (no_imprime != vazio) {
        In_Ordem(no_imprime->getLeft()); 
        std::cout << no_imprime->getId() << std::endl;
        In_Ordem(no_imprime->getRight());
    }
}
