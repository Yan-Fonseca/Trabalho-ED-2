#include "../include/Multinode.h"

Multinode::Multinode(int s){
    
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

    sons.reserve(s);
    nodes.reserve(s);
        
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
void Multinode::insert_son(Multinode* son,int* comp){

    *comp++;
    if(son==nullptr){
        return;
    }

    std::string maiorId = son->getNode(son->getContains()-1)->getId();

    for(int i=0;i<contains;i++){
        *comp++;
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

Multinode* Multinode::findSon(std::string id,int* comp){
    
    *comp++;
    if(sons[0]==nullptr)
        return nullptr;
    for(int i=0;i<contains;i++){
        *comp++;
        if(id.compare(nodes[i]->getId())<=0)
            return sons[i];
    }
    return sons[contains];
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

void Multinode::insert(No* node,bool balance,int* comp){

    if(contains==0){
        nodes[0]=node;
        contains++;
        return;
    }
        

    std::string id = node->getId();

    //std::cout<<nodes[0]->getId()<<" "<<nodes[contains-1]->getId()<<"\n";

    *comp++;
    if(id.compare(nodes[0]->getId())<=0)
        insertSort(node,0,balance,comp);

    else{
        *comp++;
        if(id.compare(nodes[contains-1]->getId())>0)
            insertSort(node,contains,balance,comp);

        else for(int i=1;i<contains;i++){
            *comp++;
            if(id.compare(nodes[i-1]->getId())>=0 && id.compare(nodes[i]->getId())<=0){
                insertSort(node,i,balance,comp);
                break;
            }
        }
    }
}

void Multinode::insertSort(No* node,int index,bool balance,int* comp){
    
    No* aux;

    *comp++;
    if(index==contains){
        nodes[index]=node;
    }
    else{
        int i=index;
        for(;(i<order-1)&&(node != nullptr);i++){
            aux = nodes[i];
            nodes[i] = node;
            node = aux;
            *comp++;
        }
        *comp++;
        if(i==contains){
            nodes[i]=node;
            
        }
    }

    contains++;

    if(balance)
        autoBalance(comp);
}

void Multinode::autoBalance(int* comp){

    *comp++;
    if (order>contains)
        return;
    
    else
    {
        if(isFolha)
            balanceFolha(comp);
        else
            balanceRaiz(comp);
    }
}

void Multinode::balanceRaiz(int* comp){

    int meio = (contains-1)/2; 

    int cesq=0,cdir=0;

    Multinode* esq = new Multinode(order,this);
    Multinode* dir = new Multinode(order,this);

    for(int i=0;i<order;i++){
        *comp++;
        if(i<meio){
            esq->setNode(nodes[i],i);
            esq->setSon(sons[i],i);
            nodes[i]=nullptr;
            sons[i]=nullptr;
            cesq++;
        }
            
        else{
            *comp++;
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

void Multinode::balanceFolha(int* comp){

    Multinode** oldSons = dad->getSons();

    
    int meio = (contains-1)/2; 

    int cesq=0,cdir=0;

    Multinode* esq = new Multinode(order,dad);
    Multinode* dir = new Multinode(order,dad);


   for(int i=0;i<order;i++){
        *comp++;
        if(i<meio){
            esq->setNode(nodes[i],i);
            esq->setSon(sons[i],i);
            nodes[i]=nullptr;
            sons[i]=nullptr;
            cesq++;
        }
            
        else{
            *comp++;
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

    dad->insert(nodes[meio],false,comp);
    dad->removeSon(this);

    for(int j=0;(j<order)&&(oldSons[j]!=nullptr);j++){
        *comp++;
        if(oldSons[j]==this)
            continue;
        else
            dad->insert_son(oldSons[j],comp);
    }
    dad->insert_son(esq,comp);
    dad->insert_son(dir,comp);
    
    nodes[meio]=nullptr;

    dad->autoBalance(comp);

    //delete this;

}

void Multinode::removeSon(Multinode* s){
    for(int i=0;i<=contains;i++)
        if(sons[i]==s){
            sons[i]=nullptr;
            return;
        }
}