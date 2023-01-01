#include "node.h"

class Multinode
{
private:
    Multinode* dad;
    int order; //n de nodes
    std::vector<Node*> nodes;
    std::vector<Multinode*> sons;
    bool isFolha;
    int contains; //n de nodes atual

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
    Node* getNode(int i);
    Multinode* getSon(int i);
    Multinode* findSon(std::string id);
    bool getIsFolha(){return isFolha;}

    void insert(Node* node);
    void remove(Node node);
    void remove(int index);
    void insert_son(Multinode* son);
    void insertSort(Node* node,int index);
    
};


class ArvoreB
{
private:
    Multinode* raiz;
    int depth;
public:
    ArvoreB();
    ArvoreB(int size);
    ~ArvoreB();
    void insere(ProductReview *pr);
    ProductReview* busca(std::string userId, std::string productId);
    int getDepth();
    void print();
    void print(Multinode* raiz);
};

ArvoreB::ArvoreB(int size){raiz = new Multinode(size);}

ArvoreB::~ArvoreB()
{
}
