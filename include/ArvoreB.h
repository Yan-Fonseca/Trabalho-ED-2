#ifndef ARVOREB_H
#define ARVOREB_H

#include "No.h"

class Multinode
{
private:
    Multinode* dad;
    int order; //n de nodes
    std::vector<No*> nodes;
    std::vector<Multinode*> sons;
    bool isFolha;
    int contains=0; //n de nodes atual

    void autoBalance();
    void balanceRaiz();
    void balanceFolha();

public:
    Multinode();
    Multinode(int s);
    Multinode(int s,Multinode* d);
    ~Multinode();

    int getContains(){return contains;}
    int getNodesN(){return nodes.size();}
    No* getNode(int i);
    Multinode* getSon(int i);
    std::vector<Multinode*> getSons();
    Multinode* findSon(std::string id);
    bool getIsFolha(){return isFolha;}

    void setContains(int c){contains=c;}
    void setOrder(int o){order=o;};
    void setIsFolha(bool ifo){isFolha=ifo;};
    void setNode(No* n, int index){nodes[index]=n;};
    void setSon(Multinode* mn, int index){sons[index]=mn;};
    void adjustSons();

    void insert(No* node,bool balance);
    void remove(No node);
    void remove(int index);
    void removeSon(Multinode* s);
    void insert_son(Multinode* son);
    void insertSort(No* node,int index,bool balance);
    
};


class ArvoreB
{
private:
    Multinode* raiz;
    int depth;
    
public:
    ArvoreB();
    ArvoreB(int size){raiz = new Multinode(size);depth=0;};
    ~ArvoreB(){delete raiz;};
    void insere(ProductReview *pr);
    void insere(std::string id);
    ProductReview* busca(std::string userId, std::string productId);
    int getDepth();
    void print();
    void print(Multinode* raiz);
};

#endif