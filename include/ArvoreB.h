#ifndef ARVOREB_H
#define ARVOREB_H

#include "Multinode.h"

class ArvoreB
{
private:
    Multinode* raiz;
    long depth;
    long comp;
    
public:
    ArvoreB();
    ArvoreB(int size);
    ~ArvoreB();
    void insere(ProductReview *pr);
    void insere(std::string id);
    ProductReview* busca(std::string userId, std::string productId);
    long getDepth();
    long getComp(){return comp;};
    void print();
    void print(Multinode* raiz);
    void resetComp(){comp=0;};

    void addComp(){comp = comp + 1;}
};

#endif