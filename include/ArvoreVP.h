#ifndef ARVOREVP_H
#define ARVOREVP_H

#include "NoVP.h"
//a
class ArvoreVP {
private:
    NoVP *raiz, *vazio;
    void LeftRotate(NoVP* novp);
    void RightRotate(NoVP* novp);
    void Balanceamento_Insere(NoVP*& novp);
    void In_Ordem(NoVP* raiz);

public:
    ArvoreVP();
    ~ArvoreVP();
    void insere(ProductReview *pr);
    ProductReview* busca(std::string userId,std::string productId);
    void print();
    //para testes
    void insere(std::string str);
};

#endif