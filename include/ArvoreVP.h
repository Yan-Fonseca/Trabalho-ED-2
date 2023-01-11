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
    void Print();
    void insere(ProductReview *pr);
    void insere(std::string str);
    ProductReview* busca(std::string userId,std::string productId);
    void print();
    
};

#endif