#include "../include/List.h"

int HashList::getTAM(){
    return TAM;
}

HashList::Node::Node(long key)
{
    this->key = key;
    this->prox = NULL;
}

HashList::Node::~Node(){}
    
long HashList::Node::getkey() {return key;}

HashList::Node* HashList::Node::getProx() {return this->prox;}

void HashList::Node::setProx(Node *p) {this->prox = p;}

HashList::List::List() 
{
    this->first = NULL;
    this->tam = 0;
}

HashList::List::~List(){this->first = NULL;}

bool HashList::List::empty()
{
    return (this->first == NULL);
}

void HashList::List::inserirNaLista(long key) {
    Node* new_node = new Node(key);

    if(new_node != NULL)
    {
        new_node->setProx(this->first);
        this->first = new_node;
        this->tam++;
    }
}

bool HashList::List::checkElement(long key) 
{
    Node *tmp = this->first;

    while(tmp != NULL && tmp->getkey() != key) 
    {
        tmp = tmp->getProx();
    }
    
    if (tmp != NULL)
        return true;
    
    return false;
}


void HashList::initializeTable (HashList::List table[]) 
{
    for(int i = 0;i < TAM;i++) {
        HashList::List* tmp = new HashList::List;
        table[i] = *tmp;
    }
}

int HashList::hashFunction(long key) {
    /*const int p = 53;
    int h = 0;
    long long p_power = 1;
    for(int i=0; i<key.size(); i++) {
        h = (h + key[i]*p_power) % TAM;
        p_power = (p_power * p) % TAM;
    }

    return h;*/

    return key % TAM;
}

bool HashList::insertInHash (HashList::List table[], long key) 
{ 
    int id = hashFunction(key);
    HashList::List aux = table[id];

    if(!aux.checkElement(key))
    {
        aux.inserirNaLista(key);
        return true;
    }

    return false;

}