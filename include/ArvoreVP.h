#ifndef ARVOREVP_H
#define ARVOREVP_H

#include "NoVP.h"

class ArvoreVP {
private:
    NoVP *raiz, *vazio;
    void LeftRotate(NoVP* novp);
    void RightRotate(NoVP* novp);
    void Balanceamento_Insere(NoVP*& novp);
    void In_Ordem(NoVP* raiz);
    int comp;
public:
    ArvoreVP();
    ~ArvoreVP();

    int* getComp(){return &comp;}
    void insere(ProductReview *pr);
    ProductReview* busca(std::string userId,std::string productId);
    void print();
    void resetComp(){comp=0;};
};

#endif