#ifndef LIST
#define LIST
#define TAM 7919

#include "iostream"

namespace HashList {

    int getTAM();

    class Node
    {
    private:
        long key;
        Node* prox;
    public:
        Node(long key);
        ~Node();
    
        long getkey();
        Node* getProx();
        void setProx(Node *p);
    };

    class List
    {
    private:
        Node *first;
        int tam;
    public:
        List();
        ~List();
    
        bool empty();

        void inserirNaLista(long key);

        bool checkElement(long key);

    };
        
    void initializeTable (HashList::List table[]) ;

    int hashFunction(long key);

    bool insertInHash (HashList::List table[], long key);

    
}  
#endif