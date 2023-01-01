#include "../include/ArvoreB.h"

//Multinode

Multinode::Multinode(int s){
    
    
    order=s;
    contains=0;
    for(int i=0;i<order;i++){
        nodes[i]=nullptr;
        sons[i]=nullptr;
    }
    sons[order]=nullptr;
}

Multinode::Multinode(int s,Multinode* d){
    
    dad = d;
    order=s;
    contains=0;
    for(int i=0;i<order;i++){
        nodes[i]=nullptr;
        sons[i]=nullptr;
    }
    sons[order]=nullptr;
}


Multinode::~Multinode(){
    nodes.clear();
    sons.clear();
}

void Multinode::remove(Node node){
    
}
void Multinode::remove(int index){
    
}
void Multinode::insert_son(Multinode* son){
    
}

Node* Multinode::getNode(int i){
    
    if(i>=0&&i<contains)
        return nodes[i];
    else
        return nullptr;
}

Multinode* Multinode::getSon(int i){
    
    if(i>=0 && i<contains+1)
        return sons[i];
    else
        return nullptr;
}

Multinode* Multinode::findSon(std::string id){
    if(sons[0]==nullptr)
        return nullptr;
    for(int i=0;i<contains;i++){
        if(id.compare(nodes[i]->getId())<0)
            return sons[i];
    }
    return sons[contains];
}

void Multinode::insert(Node* node){

    if(contains=0){
        nodes[0]=node;
        return;
    }

    std::string id = node->getId();

    if(id.compare(nodes[0]->getId())<0)
        insertSort(node,0);

    else if(id.compare(nodes[contains-1]->getId())>0)
        insertSort(node,contains);

    else for(int i=1;i<contains;i++){
        if(id.compare(nodes[i-1]->getId())>=0 && id.compare(nodes[i]->getId())<=0){
            insertSort(node,i);
            break;
        }
    }
    
}

void Multinode::insertSort(Node* node,int index){

    Node* aux;

    
    for(int i=index;(i<order-1)&&(node != nullptr);i++){
        aux = nodes[i];
        nodes[i] = node;
        node = aux;
    }

    contains++;

    autoBalance();
}

void Multinode::autoBalance(){
    if (order>contains)
        return;
    
    else
    {
        if(isFolha)
            balanceFolha();
        else
            balanceRaiz();
    }
}

void Multinode::balanceRaiz(){

    int meio = (contains-1)/2; 

    Multinode* esq = new Multinode(order,this);
    Multinode* dir = new Multinode(order,this);

    esq->insert_son(sons[meio]);
    dir->insert_son(sons[order]);
    sons[meio]=nullptr;
    sons[order]=nullptr;
    for(int i=0;i<contains;i++){
        if(i<meio){
            esq->insert(nodes[i]);
            esq->insert_son(sons[i]);
            nodes[i]=nullptr;
            sons[i]=nullptr;
        }
            
        else if(i>meio){
            dir->insert(nodes[i]);
            dir->insert_son(sons[i]);
            nodes[i]=nullptr;
            sons[i]=nullptr;
        }
    }
    nodes[0]=nodes[meio];
    nodes[meio]=nullptr;
    sons[0]=esq;
    sons[1]=dir;

}

void Multinode::balanceFolha(){
    int meio = (contains-1)/2; 

    Multinode* esq = new Multinode(order,this);
    Multinode* dir = new Multinode(order,this);

    esq->insert_son(sons[meio]);
    dir->insert_son(sons[order]);
    sons[meio]=nullptr;
    sons[order]=nullptr;
    for(int i=0;i<contains;i++){
        if(i<meio){
            esq->insert(nodes[i]);
            esq->insert_son(sons[i]);
            nodes[i]=nullptr;
            sons[i]=nullptr;
        }
            
        else if(i>meio){
            dir->insert(nodes[i]);
            dir->insert_son(sons[i]);
            nodes[i]=nullptr;
            sons[i]=nullptr;
        }
    }

    dad->insert(nodes[meio]);
    dad->insert_son(esq);
    dad->insert_son(dir);

    nodes[meio]=nullptr;

    //delete this;

}




// ArvoreB
void ArvoreB::insere(ProductReview* pr){

    Node* node = new Node(pr);


    Multinode* son = raiz;
    for(int i=0;i<depth;i++){
        son = son->findSon(node->getId());
        if(son==nullptr)
            break;
        else    
            if(i==depth-1)
                std::cout<<"Error ArvoreB::insere\n";
    }
    son->insert(node);
    
    depth=getDepth();

}

/* ProductReview* ArvoreB::busca(std::string userId, std::string productId){

    std::string id = userId + productId;

    Multinode* n = raiz;

    for(int y = 0; y< depth; y++){
        for(int i=0;i<n->getNodesN();i++){
        if(id<n->getNode(i)->getId())
            n->getSon(i)->busca(userId,productId);
    }
    
    }

} */

int ArvoreB::getDepth(){
    int d=0;
    Multinode* son=raiz;
    while(son!=nullptr){
        d++;
        son=son->getSon(0);
    }
    return d;
}

void ArvoreB::print(){
    int i;
  for (i = 0; i < raiz->getContains(); i++) {
    // Imprime a chave atual
    std::cout << raiz->getNode(i)->getId() << " ";

    // Imprime os filhos se existirem
    if (!raiz->getIsFolha())
      print(raiz->getSon(i));
  }

  // Imprime o último filho, se existir
  if (!raiz->getIsFolha())
      print(raiz->getSon(i));
}

void ArvoreB::print(Multinode* mn){
    int i;
  for (i = 0; i < mn->getContains(); i++) {
    // Imprime a chave atual
    std::cout << mn->getNode(i)->getId() << " ";

    // Imprime os filhos se existirem
    if (!mn->getIsFolha())
      print(mn->getSon(i));
  }

  // Imprime o último filho, se existir
  if (!mn->getIsFolha())
      print(mn->getSon(i));
}