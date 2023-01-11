#ifndef NoVP_H
#define NoVP_H

#include <iostream>
#include <string>
#include "ProductReview.h"

class NoVP
{
private:
    std::string id;
    long int binary_position;
    ProductReview* base;
public:
    NoVP *Esq, *Dir;
    int cor;

    NoVP(){id="null";binary_position=-1;};
    NoVP(ProductReview* pr){id = pr->getUserId()+""+pr->getProductId(); base = pr; binary_position=pr->getBinaryPosition();};

    //para testes
    NoVP(std::string ID){ id = ID;};
    
    ~NoVP(){};

    int getPosition();
    std::string getId(){return id;}
    ProductReview* getBase(){return base;};
};

#endif