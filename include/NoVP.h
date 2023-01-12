#ifndef NoVP_H
#define NoVP_H

#include <iostream>
#include <string>
#include "ProductReview.h"

enum class COR {
    RED,
    BLACK
};

class NoVP{
    private:
    long int binary_position;
    ProductReview* base;
    std::string valorid;
    COR cor;
public:
    NoVP *left, *right, *pai;
    std::string getid(){return valorid;};
    COR getcor(){return cor;};
    COR setcor(COR c){
        cor = c;
    }
    NoVP(std::string val, COR c) : valorid(val), cor(c), left(nullptr), right(nullptr), pai(nullptr) {}


    NoVP(){valorid="null";binary_position=-1;};
    NoVP(ProductReview* pr){valorid = pr->getUserId()+""+pr->getProductId(); base = pr; binary_position=pr->getBinaryPosition();};

    //para testes
    NoVP(std::string ID){ valorid = ID;};
    
    ~NoVP(){};

    int getPosition();
    std::string getId(){return valorid;}
    ProductReview* getBase(){return base;};
};

#endif