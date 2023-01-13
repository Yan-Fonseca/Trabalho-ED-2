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
    int comp;
public:
    ArvoreVP();
    ~ArvoreVP();

    int* getComp(){return &comp;};
    void setComp(int c){comp = c;};
    void addcomp(){comp++;};
    void insere(ProductReview *pr);
    ProductReview* busca(std::string userId,std::string productId);
    void print();
};

#endif