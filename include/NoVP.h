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
    NoVP *left, *right, *pai;
public:

    void setPai(NoVP* novp) { pai = novp; }
    NoVP* getPai() { return pai; }
    void setLeft(NoVP* novp) { left = novp; }
    NoVP* getLeft() { return left; }
    void setRight(NoVP* novp) { right = novp; }
    NoVP* getRight() { return right; }

    std::string getId(){return valorid;}
    
    ProductReview* getBase(){ return base;}; //ponteiro pro nó do ProductReview

    COR getCor(){return cor;};
    void setCor(COR c){cor = c;}

    NoVP(std::string val, COR c,ProductReview* pr) : binary_position( pr->getBinaryPosition()), base(pr), valorid(val), cor(c), left(nullptr), right(nullptr), pai(nullptr) {}
    
    NoVP(){valorid="null";binary_position=-1;};
    ~NoVP(){};

    int getPosition();
};

#endif