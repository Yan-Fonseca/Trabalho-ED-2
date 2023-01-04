#include "../include/ArvoreB.h"

//Multinode

Multinode::Multinode(int s){
    
    dad=nullptr;
    setOrder(s);
    setContains(0);
    setIsFolha(false);
    for(int i=0;i<order;i++){
        nodes.push_back(nullptr);
        sons.push_back(nullptr);
    }
    sons.push_back(nullptr);
}

void Multinode::setSon(Multinode* mn, int index){
    sons[index]=mn;
    if(mn!=nullptr)
        mn->setDad(this);
}

Multinode::Multinode(int s,Multinode* d){
    
    dad = d;
    setOrder(s);
    setContains(0);
    setIsFolha(true);
    for(int i=0;i<order;i++){
        nodes.push_back(nullptr);
        sons.push_back(nullptr);
    }
    sons.push_back(nullptr);
}


Multinode::~Multinode(){
    for(int i=0;i<contains;i++){
        delete nodes[i];
        delete sons[i];
    }
    delete sons[contains];
    nodes.clear();
    sons.clear();
}

void Multinode::remove(No node){
    
}
void Multinode::remove(int index){
    
}
void Multinode::insert_son(Multinode* son){
    if(son==nullptr){
        return;
    }

    std::string maiorId = son->getNode(son->getContains()-1)->getId();

    for(int i=0;i<contains;i++){
        if(maiorId.compare(nodes[i]->getId())<=0){
            sons[i]=son;
            return;
        }
    }
    sons[contains]=son;
}

No* Multinode::getNode(int i){
    
    if(i>=0&&i<contains)
        return nodes.at(i);
    else
        return nullptr;
}

Multinode* Multinode::getSon(int i){
    
    if(i>=0 && i<contains+1)
        return sons.at(i);
    else
        return nullptr;
}

Multinode* Multinode::findSon(std::string id){
    if(sons[0]==nullptr)
        return nullptr;
    for(int i=0;i<contains;i++){
        if(id.compare(nodes[i]->getId())<=0)
            return sons[i];
    }
    return sons[contains];
}

void Multinode::insert(No* node,bool balance){

    if(contains==0){
        nodes[0]=node;
        contains++;
        return;
    }
        

    std::string id = node->getId();

    //std::cout<<nodes[0]->getId()<<" "<<nodes[contains-1]->getId()<<"\n";

    if(id.compare(nodes[0]->getId())<=0)
        insertSort(node,0,balance);

    else if(id.compare(nodes[contains-1]->getId())>0)
        insertSort(node,contains,balance);

    else for(int i=1;i<contains;i++){
        if(id.compare(nodes[i-1]->getId())>=0 && id.compare(nodes[i]->getId())<=0){
            insertSort(node,i,balance);
            break;
        }
    }
    
}

void Multinode::insertSort(No* node,int index,bool balance){

    No* aux;

    if(index==contains){
        nodes[index]=node;
    }
    else{
        int i=index;
        for(;(i<order-1)&&(node != nullptr);i++){
            aux = nodes[i];
            nodes[i] = node;
            node = aux;
        }
        if(i==contains){
            nodes[i]=node;
    }
    }

    contains++;

    if(balance)
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

    int cesq=0,cdir=0;

    Multinode* esq = new Multinode(order,this);
    Multinode* dir = new Multinode(order,this);

    for(int i=0;i<order;i++){
        if(i<meio){
            esq->setNode(nodes[i],i);
            esq->setSon(sons[i],i);
            nodes[i]=nullptr;
            sons[i]=nullptr;
            cesq++;
        }
            
        else if(i>meio){
            dir->setNode(nodes[i],i-meio-1);
            dir->setSon(sons[i],i-meio-1);
            nodes[i]=nullptr;
            sons[i]=nullptr;
            cdir++;
        }
    }

    esq->setSon(sons[meio],cesq);
    dir->setSon(sons[order],cdir);
    sons[meio]=nullptr;
    sons[order]=nullptr;    

    nodes[0]=nodes[meio];
    nodes[meio]=nullptr;
    sons[0]=esq;
    sons[1]=dir;

    setContains(1);
    esq->setContains(cesq);
    dir->setContains(cdir);


}

Multinode** Multinode::getSons(){
    Multinode** s = new Multinode*[order];
    for(unsigned int i=0;i<sons.size();i++){
        s[i]=sons.at(i);
    }
    return s;
}

void Multinode::balanceFolha(){

    /* std::vector<Multinode*> oldSons(3); */
    /* for(int i=0;i<=dad->getContains();i++){
        oldSons.push_back(dad->getSon(i));
    } */
    Multinode** oldSons = dad->getSons();

    
    int meio = (contains-1)/2; 

    int cesq=0,cdir=0;

    Multinode* esq = new Multinode(order,dad);
    Multinode* dir = new Multinode(order,dad);


   for(int i=0;i<order;i++){
        std::cout<<nodes[i]->getId()<<" ";
        if(i<meio){
            esq->setNode(nodes[i],i);
            esq->setSon(sons[i],i);
            nodes[i]=nullptr;
            sons[i]=nullptr;
            cesq++;
        }
            
        else if(i>meio){
            dir->setNode(nodes[i],i-meio-1);
            dir->setSon(sons[i],i-meio-1);
            nodes[i]=nullptr;
            sons[i]=nullptr;
            cdir++;
        }
    }
    std::cout<<"\n";

    esq->setSon(sons[meio],cesq);
    dir->setSon(sons[order],cdir);
    sons[meio]=nullptr;
    sons[order]=nullptr;  

    setContains(1);
    esq->setContains(cesq);
    dir->setContains(cdir);

    dad->insert(nodes[meio],false);
    dad->removeSon(this);

    for(int j=0;(j<order)&&(oldSons[j]!=nullptr);j++){
        if(oldSons[j]==this)
            continue;
        else
            dad->insert_son(oldSons[j]);
    }
    dad->insert_son(esq);
    dad->insert_son(dir);

    /* oldSons = dad->getSons();
    for(int i=0;i<=order;i++){
        std::cout<<oldSons[i]->getNode(0)->getId()<<" ";
    std::cout<<"\n"; */
    
    nodes[meio]=nullptr;

    dad->autoBalance();

    //delete this;

}

void Multinode::removeSon(Multinode* s){
    for(int i=0;i<=contains;i++)
        if(sons[i]==s){
            sons[i]=nullptr;
            return;
        }
}


// ArvoreB
void ArvoreB::insere(ProductReview* pr){

    No* node = new No(pr);


    Multinode* son = raiz;
    for(int i=0;i<depth;i++){
        son = son->findSon(node->getId());
        if(son==nullptr)
            break;
        else    
            if(i==depth-1)
                std::cout<<"Error ArvoreB::insere\n";
    }
    son->insert(node,true);
    
    depth=getDepth();

}

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
    return d-1;
}

void ArvoreB::print(){
    int i;
    for (i = 0; i < raiz->getContains(); i++) {
        // Imprime a chave atual
        std::cout << raiz->getNode(i)->getId() << " ";

        // Imprime os filhos se existirem
    }
    std::cout<<" - raiz";
    for(i = 0; i <= raiz->getContains(); i++){
        Multinode* son = raiz->getSon(i);
        if (son!=nullptr)
            print(son,std::to_string(i));
        
        //std::cout<<" - filho "<<i;
    }
    std::cout<<"\n\n";

}

void ArvoreB::print(Multinode* mn,std::string rank){
    int i;
    std::cout<<"\n";
    for (i = 0; i < mn->getContains(); i++) {
        // Imprime a chave atual
        std::cout << mn->getNode(i)->getId() << " ";
    }
    std::cout<<" - filho "<<rank;
    Multinode* son=raiz;
    for(i = 0; (i <= mn->getContains())&&(son!=nullptr); i++){
        Multinode* son = mn->getSon(i);
        if (son!=nullptr)
            print(son,rank+"."+std::to_string(i));
    }
}