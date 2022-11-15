#include "iostream"
namespace HashList {
    #ifndef LIST
    #define LIST
    #define TAM 7919

    int getTAM(){
        return TAM;
    }

    class Node
    {
    private:
        std::string key;
        Node* prox;
    public:
        Node(std::string key)
        {
            this->key = key;
            this->prox = NULL;
        }
        ~Node();
    
        std::string getkey() {return key;}
        Node* getProx() {return this->prox;}
        void setProx(Node *p) {this->prox = p;}
    };

    class List
    {
    private:
        Node *first;
        int tam;
    public:
        List() 
        {
            this->first = NULL;
            this->tam = 0;
        }
        ~List(){this->first = NULL;}
    
    bool empty()
    {
        return (this->first == NULL);
    }

    void inserirNaLista(std::string key) {
        Node* new_node = new Node(key);

        if(new_node != NULL)
        {
            new_node->setProx(this->first);
            this->first = new_node;
            this->tam++;
        }
    }

    bool checkElement(std::string key) 
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

    };
    
    void initializeTable (HashList::List table[]) 
    {
        for(int i = 0;i < TAM;i++) {
            HashList::List* tmp = new HashList::List;
            table[i] = *tmp;
        }
    }

    int hashFunction(std::string key) {
        const int p = 53;
        int h = 0;
        long long p_power = 1;
        for(int i=0; i<key.size(); i++) {
            h = (h + key[i]*p_power) % TAM;
            p_power = (p_power * p) % TAM;
        }

        return h;
    }

    bool insertInHash (HashList::List table[], std::string key) 
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

    #endif
}