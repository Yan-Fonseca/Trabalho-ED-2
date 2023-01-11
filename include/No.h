#ifndef NO_H
#define NO_H

#include <iostream>
#include <string>
#include "ProductReview.h"

class No
{
private:
    std::string id;
    long int binary_position;
    ProductReview* base;
public:
    No(){id="null";binary_position=-1;};
    No(ProductReview* pr){id = pr->getUserId()+""+pr->getProductId(); base = pr; binary_position=pr->getBinaryPosition();};

    //para testes
    No(std::string ID){ id = ID;};
    
    ~No(){};

    int getPosition();
    std::string getId(){return id;}
    ProductReview* getBase(){return base;};
};

#endif