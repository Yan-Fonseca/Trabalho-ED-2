#include "../include/ArvoreB.h"

ArvoreB::ArvoreB(int size){
    raiz = new Multinode(size-1,&comp);
    depth=0;
    comp=0;
}

ArvoreB::~ArvoreB(){
    raiz->~Multinode();
    delete raiz;
}

void ArvoreB::insere(ProductReview* pr){

    No* node = new No(pr);

    //std::cout<<pr->getBinaryPosition()<<"\n";


    Multinode* son = raiz;
    for(int i=0;i<depth;i++){
        son = son->findSon(node->getId());
        if(son->getSon(0)==nullptr)
            break;
        else    
            if(i==depth-1)
                std::cout<<"Error ArvoreB::insere\n";
    }
    son->insert(node,true);
    
    depth=getDepth( );

}

//Só para testes
void ArvoreB::insere(std::string id){

    No* node = new No(id);

    Multinode* son = raiz;
    for(int i=0;i<depth;i++){
        son = son->findSon(node->getId());
        if(son->getSon(0)==nullptr)
            break;
        else    
            if(i==depth-1)
                std::cout<<"Error ArvoreB::insere\n";
    }
    son->insert(node,true);
    
    depth=getDepth();

}

ProductReview* ArvoreB::busca(std::string userId, std::string productId){

    std::string id = userId + productId;

    Multinode* son = raiz;

    for(int i=0;i<depth;i++){
        son = son->findSon(id);
        addComp();
        if(son->getSon(0)==nullptr)
            break;
        else {
            addComp();
            if(i==depth-1)
                std::cout<<"Error ArvoreB::busca\n";
        }   
            
    }
    bool found = false;
    int i;
    for(i = 0; i< son->getContains(); i++){
        addComp();
        if(id == son->getNode(i)->getId()){
            found=true;
            break;
        } 
    }
    addComp();
    if(!found)
        return nullptr;
    
    ProductReview* pr = new ProductReview(son->getNode(i)->getBase());

    return pr;
}

long ArvoreB::getDepth(){
    long d=0;
    Multinode* son=raiz;
    while(son!=nullptr){
        d++;
        son=son->getSon(0);
        addComp();
    return d-1;
    }
    return -1;
}

void ArvoreB::print(){
    print(raiz);
}


void ArvoreB::print(Multinode* mn){
    int i;
    if (mn == nullptr) return;

    print(mn->getSon(0));

    for (i = 0; i < mn->getContains(); i++) {
        std::cout << mn->getNode(i)->getId() << " ";
    }

    for (i = 1; i <= mn->getContains(); i++) {
        print(mn->getSon(i));
    }
}