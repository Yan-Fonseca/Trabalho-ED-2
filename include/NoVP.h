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

    void setPai(NoVP* node) { pai = node; }
    NoVP* getPai() { return pai; }
    void setLeft(NoVP* node) { left = node; }
    NoVP* getLeft() { return left; }
    void setRight(NoVP* node) { right = node; }
    NoVP* getRight() { return right; }

    std::string getId(){return valorid;}

    ProductReview* getBase(){return base;};

    COR getCor(){return cor;};
    void setCor(COR c){cor = c;}

    NoVP(std::string val, COR c,ProductReview* pr) : binary_position( pr->getBinaryPosition()), base(pr), valorid(val), cor(c), left(nullptr), right(nullptr), pai(nullptr) {}
    
    NoVP(){valorid="null";binary_position=-1;};
    ~NoVP(){};

    int getPosition();
};

#endif