#include "../include/Multinode.h"
#include <stack>

Multinode::Multinode(int s,long* c){
    
    comp = c;
    dad=nullptr;
    setOrder(s);
    setContains(0);
    setIsFolha(false);

    nodes.reserve(s);

    for(int i=0;i<order;i++){
        nodes.push_back(nullptr);
        sons.push_back(nullptr);
    }
    sons.push_back(nullptr);
}

Multinode::Multinode(int s,Multinode* d,long* c){
    
    comp = c;
    dad = d;
    setOrder(s);
    setContains(0);
    setIsFolha(true);

    sons.reserve(s);
    nodes.reserve(s);
        
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

Multinode::~Multinode() {
    for(auto son : sons) {
        if (son != nullptr) {
            delete son;
        }
    }
    for(auto node : nodes) {
        if (node != nullptr) {
            delete node;
        }
    }
}

void Multinode::insert_son(Multinode* son ){

    addComp();;
    if(son==nullptr){
        return;
    }

    std::string maiorId = son->getNode(son->getContains()-1)->getId();

    for(int i=0;i<contains;i++){
        addComp();;
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

Multinode* Multinode::findSon(std::string id ){
    
    addComp();;
    if(sons[0]==nullptr)
        return nullptr;
    for(int i=0;i<contains;i++){
        addComp();;
        if(id.compare(nodes[i]->getId())<=0)
            return sons[i];
    }
    return sons[contains];
}


void Multinode::insert(No* node,bool balance ){

    if(contains==0){
        nodes[0]=node;
        contains++;
        return;
    }
        

    std::string id = node->getId();

    //std::cout<<nodes[0]->getId()<<" "<<nodes[contains-1]->getId()<<"\n";

    addComp();;
    if(id.compare(nodes[0]->getId())<=0)
        insertSort(node,0,balance);

    else{
        addComp();;
        if(id.compare(nodes[contains-1]->getId())>0)
            insertSort(node,contains,balance);

        else for(int i=1;i<contains;i++){
            addComp();;
            if(id.compare(nodes[i-1]->getId())>=0 && id.compare(nodes[i]->getId())<=0){
                insertSort(node,i,balance);
                break;
            }
        }
    }
}

void Multinode::insertSort(No* node,int index,bool balance ){
    
    No* aux;

    addComp();
    if(index==contains){
        nodes[index]=node;
    }
    else{
        int i=index;
        for(;(i<order-1)&&(node != nullptr);i++){
            aux = nodes[i];
            nodes[i] = node;
            node = aux;
            addComp();;
        }
        addComp();;
        if(i==contains){
            nodes[i]=node;
            
        }
    }

    contains++;

    if(balance)
        autoBalance();
}

void Multinode::autoBalance( ){

    addComp();
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

void Multinode::balanceRaiz( ){

    int meio = (contains-1)/2; 

    int cesq=0,cdir=0;

    Multinode* esq = new Multinode(order,this,comp);
    Multinode* dir = new Multinode(order,this,comp);

    for(int i=0;i<order;i++){
        addComp();;
        if(i<meio){
            esq->setNode(nodes[i],i);
            esq->setSon(sons[i],i);
            nodes[i]=nullptr;
            sons[i]=nullptr;
            cesq++;
        }
            
        else{
            addComp();;
            if(i>meio){
                dir->setNode(nodes[i],i-meio-1);
                dir->setSon(sons[i],i-meio-1);
                nodes[i]=nullptr;
                sons[i]=nullptr;
                cdir++;
             }
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

void Multinode::balanceFolha( ){

    Multinode** oldSons = dad->getSons();

    
    int meio = (contains-1)/2; 

    int cesq=0,cdir=0;

    Multinode* esq = new Multinode(order,dad,comp);
    Multinode* dir = new Multinode(order,dad,comp);


   for(int i=0;i<order;i++){
        addComp();;
        if(i<meio){
            esq->setNode(nodes[i],i);
            esq->setSon(sons[i],i);
            nodes[i]=nullptr;
            sons[i]=nullptr;
            cesq++;
        }
            
        else{
            addComp();;
            if(i>meio){
                dir->setNode(nodes[i],i-meio-1);
                dir->setSon(sons[i],i-meio-1);
                nodes[i]=nullptr;
                sons[i]=nullptr;
                cdir++;
             }
        } 
    }

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
        addComp();;
        if(oldSons[j]==this)
            continue;
        else
            dad->insert_son(oldSons[j]);
    }
    dad->insert_son(esq);
    dad->insert_son(dir);
    
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