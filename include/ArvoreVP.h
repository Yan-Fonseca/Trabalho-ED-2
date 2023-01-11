#ifndef ARVOREVP_H
#define ARVOREVP_H

#include "NoVP.h"

class ArvoreVP {
private:
    NoVP *raiz;
    void LeftRotate(NoVP novp);
    void RightRotate(NoVP novp);
    void InsertFixup(NoVP*& novp);

public:
    ArvoreVP();
    ~ArvoreVP();
    void insere(ProductReview *pr);
    ProductReview* busca(std::string userId,std::string productId);
    NoVP* Search(std::string userId_productId);

    void print();
    
};

#endif