#ifndef ARVOREB_H
#define ARVOREB_H

#include "Multinode.h"

class ArvoreB
{
private:
    Multinode* raiz;
    int depth;
    int comp;
    
public:
    ArvoreB();
    ArvoreB(int size);
    ~ArvoreB(){delete raiz;};
    void insere(ProductReview *pr);
    void insere(std::string id);
    ProductReview* busca(std::string userId, std::string productId);
    int getDepth();
    int getComp(){return comp;};
    void setComp(int c){comp = c;};
    void print();
    void print(Multinode* raiz);
    void resetComp(){comp=0;};

    void addComp(){comp = comp + 1;}
};

#endif