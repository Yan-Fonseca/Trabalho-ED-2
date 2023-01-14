#include "../include/ArvoreB.h"

ArvoreB::ArvoreB(int size){
    raiz = new Multinode(size-1);
    depth=0;
    comp=0;
}

void ArvoreB::insere(ProductReview* pr){

    No* node = new No(pr);


    Multinode* son = raiz;
    for(int i=0;i<depth;i++){
        son = son->findSon(node->getId());
        if(son->getSon(0)==nullptr)
            break;
        else    
            if(i==depth-1)
                std::cout<<"Error ArvoreB::insere\n";
    }
    son->insert(node,true,getComp());
    
    depth=getDepth(getComp());

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
    son->insert(node,true,getComp());
    
    depth=getDepth(getComp());

}

ProductReview* ArvoreB::busca(std::string userId, std::string productId){

    std::string id = userId + productId;

    Multinode* son = raiz;

    for(int i=0;i<depth;i++){
        son = son->findSon(id);
        if(son->getSon(0)==nullptr)
            break;
        else    
            if(i==depth-1)
                std::cout<<"Error ArvoreB::insere\n";
    }
    bool found = false;
    int i;
    for(i = 0; i< son->getContains(); i++){
        if(id == son->getNode(i)->getId()){
            found=true;
            break;
        } 
    }
    if(!found)
        return nullptr;
    
    ProductReview* pr = new ProductReview(son->getNode(i)->getBase());

    return pr;
}

int ArvoreB::getDepth(int* comp){
    int d=0;
    Multinode* son=raiz;
    while(son!=nullptr){
        d++;
        son=son->getSon(0);
        *comp++;
    }
    return d-1;
}

void ArvoreB::print(){
    int i;
    std::cout<<"Arvore B: \n";
    // Imprime a raizo atual
    for (i = 0; i < raiz->getContains(); i++) {
        std::cout << raiz->getNode(i)->getId() << " ";
    }
    std::cout<<" - raiz";

    // Imprime os filhos se existirem
    for(i = 0; i <= raiz->getContains(); i++){
        Multinode* son = raiz->getSon(i);
        if (son!=nullptr)
            print(son,std::to_string(i));
    }
    std::cout<<"\n\n";

}


void ArvoreB::print(Multinode* mn,std::string rank){
    int i;
    std::cout<<"\n";

    // Imprime o Multinode atual
    for (i = 0; i < mn->getContains(); i++) {
        std::cout << mn->getNode(i)->getId() << " ";
    }
    std::cout<<" - filho "<<rank;

    // Imprime os filhos se existirem
    Multinode* son=mn;
    for(i = 0; (i <= mn->getContains())&&(son!=nullptr); i++){
        Multinode* son = mn->getSon(i);
        if (son!=nullptr)
            print(son,rank+"."+std::to_string(i));
    }
}