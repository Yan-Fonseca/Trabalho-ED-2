#ifndef MULTINODE_H
#define MULTINODE_H

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

    void autoBalance(int* comp);
    void balanceRaiz(int* comp);
    void balanceFolha(int* comp);

public:
    Multinode();
    Multinode(int s);
    Multinode(int s,Multinode* d);
    ~Multinode();

    int getContains(){return contains;}
    int getNodesN(){return nodes.size();}
    No* getNode(int i);
    Multinode* getSon(int i);
    Multinode** getSons();
    Multinode* findSon(std::string id,int* comp);
    Multinode* findSon(std::string id);
    bool getIsFolha(){return isFolha;}

    void setContains(int c){contains=c;}
    void setOrder(int o){order=o;};
    void setIsFolha(bool ifo){isFolha=ifo;};
    void setNode(No* n, int index){nodes[index]=n;};
    void setSon(Multinode* mn, int index);
    void setDad(Multinode* mn){dad=mn;};

    void insert(No* node,bool balance,int* comp);
    void remove(No node);
    void remove(int index);
    void removeSon(Multinode* s);
    void insert_son(Multinode* son,int* comp);
    void insertSort(No* node,int index,bool balance,int* comp);
};

#endif